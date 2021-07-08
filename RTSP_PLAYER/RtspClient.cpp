#include "RtspClient.h"
#include "RtspParser.h"
#include <QRandomGenerator>

CRtspClient::CRtspClient(const QString& rtspUrl,bool isTcp)
	:m_rtspUrl(rtspUrl),m_bTcp(isTcp)
{
	QString host = m_rtspUrl.host();
	int port = m_rtspUrl.port();
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

	QByteArray buffer = pRtspSocket->readAll();
		
	printf("%s\n", buffer.data());

	processRTSP(buffer);
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
		break;
	case KSK::ERtspState_SETUP:
		break;
	case KSK::ERtspState_PLAY:
		break;
	case KSK::ERtspState_TEARDOWN:
		break;
	default:
		break;
	}
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
