#include "Define.h"
#include "RtspClient.h"
#include "RtspParser.h"
#include <WinSock2.h>
#include <QRandomGenerator>
#pragma comment(lib, "ws2_32.lib")

CRtspClient::CRtspClient(const QString& rtspUrl,bool isTcp)
	:m_rtspUrl(rtspUrl),m_bTcp(isTcp)
{
	QString host = m_rtspUrl.host();
	int port = m_rtspUrl.port();
	
	m_startCode.push_back((char)0);
	m_startCode.push_back((char)0);
	m_startCode.push_back((char)0);
	m_startCode.push_back((char)1);	
}

CRtspClient::~CRtspClient()
{
}

bool CRtspClient::initialize()
{
	m_rtcpssrc = QRandomGenerator::global()->bounded(KSK::RANDOM_MAX_NUMBER);

	m_pRtspSocket = new QTcpSocket();
		
	QObject::connect(m_pRtspSocket, &QTcpSocket::connected, this, &CRtspClient::onConneted);
	QObject::connect(m_pRtspSocket, &QTcpSocket::disconnected, this, &CRtspClient::onDisconnected);
	QObject::connect(m_pRtspSocket, &QTcpSocket::readyRead, this, &CRtspClient::onReceivedData);

	m_pRtspSocket->connectToHost(m_rtspUrl.host(), m_rtspUrl.port());

	if (m_pRtspSocket->waitForConnected() == false)
		return false;	
	
	return true;
}

void CRtspClient::uninitialize()
{
	if (m_pRtspSocket != nullptr)
	{
		m_pRtspSocket->disconnect();
		m_pRtspSocket->deleteLater();
	}
}

void CRtspClient::requestDescribeDigest(const QString& userName, const QString& realm, const QString& nonce, const QString& uri, const QString& response)
{
	QString describeMessage;

	describeMessage = CRtspParser::getInstance()->makeDescribeMethodWithDigest(m_rtspUrl.toString(), m_nSEQ++,userName,realm,nonce,uri,response);

	m_pRtspSocket->write(describeMessage.toLocal8Bit());

	m_rtspState = KSK::ERtspState_DESCRIBE;
}

void CRtspClient::onConneted()
{
	requestOptionMethod();

	printf("%s\n", __FUNCTION__);
}

void CRtspClient::onDisconnected()
{
	printf("%s\n", __FUNCTION__);
}

void CRtspClient::onReceivedData()
{	
	QTcpSocket *pRtspSocket = static_cast<QTcpSocket*>(sender());

	m_buffer += pRtspSocket->readAll();
	
	while (m_buffer.isEmpty() == false)
	{
		if (m_buffer[0] == RTP_RTCP_TCP_STD_FIRST_CHAR)
		{			
			unsigned short payloadLength = ntohs(*(unsigned short*)(m_buffer.data() + 2));
			payloadLength += RTP_RTCP_TCP_STD_HEADER_SIZE;

			if (m_buffer.length() < payloadLength)
				return;
			
			QByteArray rtpMessage = m_buffer.mid(RTP_RTCP_TCP_STD_HEADER_SIZE, payloadLength-RTP_RTCP_TCP_STD_HEADER_SIZE);
			m_buffer = m_buffer.right(m_buffer.length() - payloadLength);			
			processRTP(rtpMessage);
		}
		else
		{
			QByteArray rtspMessage = m_buffer;
			m_buffer.clear();			
			printf("%s\n", rtspMessage.data());

			processRTSP(rtspMessage);
		}
	}
}

void CRtspClient::onSendRtcp()
{
	unsigned char buffer[12];
	memset(buffer, 0x00, 12);

	buffer[0] = RTP_RTCP_TCP_STD_FIRST_CHAR;
	buffer[1] = 3; // RTCP Channel
	*((uint16_t*)(buffer + 2)) = htons((uint16_t)8);

	unsigned char* pkt = buffer + 4;

	pkt[0] |= (2 << 6) & 0xc0;
	pkt[0] |= (0 << 7) & 0x20;
	pkt[0] |= (0) & 0x1f;

	pkt[1] = 201 & 0xff;
	*((uint16_t*)(pkt + 2)) = htons(1); //Length
	*((uint32_t*)(pkt + 4)) = htonl(m_rtcpssrc); // SSRC

	m_pRtspSocket->write((char*)buffer, 12);
}

void CRtspClient::processRTSP(const QString& rtspMessage)
{
	std::map<QString, QString> headerMap;

	headerMap = CRtspParser::getInstance()->rtspResponseMessageParse(rtspMessage);

	if (headerMap.size() == 0)
		return;

	auto it = headerMap.find(RTSP_HEADER_ERROR);
	if (it != headerMap.end())
	{
		headerMap["URL"] = m_rtspUrl.toString();
		emit unAuthorizedError(headerMap);
		return;
	}		

	switch (m_rtspState)
	{
	case KSK::ERtspState_OPTION:
		requestDescribeMethod();
		break;
	case KSK::ERtspState_DESCRIBE:
	{
		auto it = headerMap.find(RTSP_SDP);
		if (it == headerMap.end())
			return;
		
		QString newUrl =  CRtspParser::getInstance()->parseSdp(it->second, m_rtspUrl.toString(), m_parameterSet);
		if (newUrl.isEmpty() == false)
			m_rtspUrl = QUrl(newUrl);

		requestSetupMethod();
		break;
	}
	case KSK::ERtspState_SETUP:
	{
		auto it = headerMap.find(RTSP_HEADER_NAME_SESSION);
		if (it == headerMap.end())
			return;

		m_sessionId = it->second;

		if (m_parameterSet.isEmpty() == false)
		{
			processSPropParameterSets();
		}

		requestPlayMethod();
		break; 
	}
	case KSK::ERtspState_PLAY:
		m_pTimer = new QTimer();
		m_pTimer->start(3000);
		connect(m_pTimer, &QTimer::timeout, this, &CRtspClient::onSendRtcp);
		break;
	case KSK::ERtspState_TEARDOWN:
		break;
	default:
		break;
	}
}

void CRtspClient::processRTP(const QByteArray& rtpData)
{
	int version = (rtpData[0] >> 6) & 3;
	//int padding,extension,csiCount;
	//int marker;
	unsigned char payloadType = rtpData[1] & 0x7F;
	unsigned short sequenceNumber = ntohs(*(unsigned short*)(rtpData.data()+2));
	unsigned int timeStamp = ntohl(*(unsigned int*)(rtpData.data()+4));
	unsigned int ssrc = ntohl(*(unsigned int*)(rtpData.data()+8));

	KSK::ENalUnit nalUnit =static_cast<KSK::ENalUnit>(rtpData[RTP_HEADER_SIZE] & 0x1F);				
		
	switch (nalUnit)
	{
	case KSK::ENalUnit_PFRAME:
		printf("ENalUnit_PFRAME\n");
		break;
	case KSK::ENalUnit_IFRAME:
		printf("ENalUnit_IFRAME\n");
		break;
	case KSK::ENalUnit_SEI:
		printf("ENalUnit_SEI\n");
		break;
	case KSK::ENalUnit_SPS:
		printf("ENalUnit_SPS\n");
		m_sps = QByteArray(rtpData.data() + RTP_HEADER_SIZE, rtpData.size() - RTP_HEADER_SIZE);
		m_sps.push_front(m_startCode);		
		break;
	case KSK::ENalUnit_PPS:
		printf("ENalUnit_PPS\n");
		m_pps = QByteArray(rtpData.data() + RTP_HEADER_SIZE, rtpData.size() - RTP_HEADER_SIZE);
		m_pps.push_front(m_startCode);
		break;
	case  KSK::ENalUnit_STAP_A:
		//printf("ENalUnit_STAP_A\n");
		processSTAP_A(QByteArray(rtpData.data() + RTP_HEADER_SIZE, rtpData.size() - RTP_HEADER_SIZE));
		break;
	case KSK::ENalUnit_FU_A:
		//printf("ENalUnit_FU_A\n");
		processFU_A(QByteArray(rtpData.data() + RTP_HEADER_SIZE, rtpData.size() - RTP_HEADER_SIZE));
		break;
	case  KSK::ENalUnit_FU_B:
		printf("ENalUnit_FU_B\n");
		break;
	default:
		printf("No define NalUnit :%d \n",nalUnit);
		break;
	}
}

void CRtspClient::processSPropParameterSets()
{
	QStringList parameterList = m_parameterSet.split(',');

	for (QString parameter : parameterList)
	{
		QByteArray decodeData = QByteArray::fromBase64(parameter.toLocal8Bit());
		KSK::ENalUnit nalType =static_cast<KSK::ENalUnit>(decodeData[0] & 0x1F);
		
		if (nalType == KSK::ENalUnit_SPS)
		{
			m_sps = decodeData;
			m_sps.push_front(m_startCode);
			printf("sps Update\n");
		}
		else if (nalType == KSK::ENalUnit_PPS)
		{
			m_pps = decodeData;
			m_pps.push_front(m_startCode);
			printf("pps Update\n");
		}
	}
}

void CRtspClient::processSingleNal(const QByteArray& rtpData)
{
	
}

void CRtspClient::processFU_A(const QByteArray& rtpData)
{
	//1. FU indicator Parse
	char fuIndicator = rtpData[0];
	char FNRI = rtpData[0] & 0xE0;

	//2. FU header Parse
	char fuHeader = rtpData[1];
	char nalType = rtpData[1] & 0x1f;
	char originNalType = FNRI | nalType;	
	
	//3. FU payload Parse
	if ((rtpData[1] & 0x80) == 0x80) // Frame Start Bit
	{
		m_frameBuffer.clear();
		m_frameBuffer.push_front(m_startCode);
		m_frameBuffer += originNalType;
		m_frameBuffer += QByteArray(rtpData.data() + RTP_FU_A_HEADER_SIZE, rtpData.size() - RTP_FU_A_HEADER_SIZE);		
	}
	else if ((rtpData[1] & 0x40) == 0x40) // Frame End Bit 
	{
		m_frameBuffer += QByteArray(rtpData.data() + RTP_FU_A_HEADER_SIZE, rtpData.size() - RTP_FU_A_HEADER_SIZE);					
		processNewFrame(static_cast<KSK::ENalUnit>(nalType));
	}
	else
		m_frameBuffer += QByteArray(rtpData.data() + RTP_FU_A_HEADER_SIZE, rtpData.size() - RTP_FU_A_HEADER_SIZE);		
	
}

void CRtspClient::processSTAP_A(const QByteArray& rtpData)
{
	QByteArray buffer = rtpData;	
	char NalHDR = buffer[0];
	buffer = buffer.right(buffer.length() - 1);

	while (buffer.isEmpty() == false)
	{
		unsigned short naluSize = ntohs(*(unsigned short*)(rtpData.data() + 1));
		naluSize += STAP_A_NALUNIT_HEADER_SIZE;

		QByteArray naluPayload = buffer.mid(STAP_A_NALUNIT_HEADER_SIZE, naluSize- STAP_A_NALUNIT_HEADER_SIZE);
		buffer = buffer.right(buffer.length() - naluSize);
		KSK::ENalUnit nalType = static_cast<KSK::ENalUnit>(naluPayload[0] & 0x1F);

		if (nalType == KSK::ENalUnit_SPS)
		{
			m_sps = naluPayload;
			m_sps.push_front(m_startCode);			
		}
		else if (nalType == KSK::ENalUnit_PPS)
		{
			m_pps = naluPayload;
			m_pps.push_front(m_startCode);			
		}
	}
}

void CRtspClient::processNewFrame(KSK::ENalUnit nalType)
{
	QByteArray frameData;
	if (nalType == KSK::ENalUnit_IFRAME)
		frameData = m_sps + m_pps + m_frameBuffer;
	else if (nalType == KSK::ENalUnit_PFRAME)		
		frameData = m_frameBuffer;
	else
		return;

	emit onNewFrame(frameData);
}

void CRtspClient::requestOptionMethod()
{
	QString optionMessage;
	
	optionMessage = CRtspParser::getInstance()->makeOptionMethod(m_rtspUrl.toString(), m_nSEQ++);
		
	m_pRtspSocket->write(optionMessage.toLocal8Bit());

	m_rtspState = KSK::ERtspState_OPTION;
}

void CRtspClient::requestDescribeMethod()
{
	QString describeMessage;

	describeMessage = CRtspParser::getInstance()->makeDescribeMethod(m_rtspUrl.toString(), m_nSEQ++);

	m_pRtspSocket->write(describeMessage.toLocal8Bit());
	
	m_rtspState = KSK::ERtspState_DESCRIBE;
}

void CRtspClient::requestSetupMethod()
{
	QString setupMessage;

	setupMessage = CRtspParser::getInstance()->makeSetupMethod(m_rtspUrl.toString(),m_nSEQ++,0);
			
	m_pRtspSocket->write(setupMessage.toLocal8Bit());

	m_rtspState = KSK::ERtspState_SETUP;
}

void CRtspClient::requestPlayMethod()
{
	QString playMessage;

	playMessage = CRtspParser::getInstance()->makePlayMethod(m_rtspUrl.toString(), m_nSEQ++, m_sessionId);

	m_pRtspSocket->write(playMessage.toLocal8Bit());

	m_rtspState = KSK::ERtspState_PLAY;
}