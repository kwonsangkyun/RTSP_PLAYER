#include "RtspParser.h"
#include "Define.h"
#include <QStringList>

CRtspParser* CRtspParser::s_pRtspParser = nullptr;

void CRtspParser::initialize()
{

}

void CRtspParser::uninitialize()
{

}

QString CRtspParser::makeOptionMethod(const QString&rtspUrl, const int seq)
{
	QString message;

	message += QString::asprintf("%s %s %s%s", RTSP_METHOD_OPTION, rtspUrl.toStdString().c_str(), RTSP_VERSION, CRLF);
	message += QString::asprintf("%s: %d%s", RTSP_HEADER_NAME_CSEQ, seq, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_USER_AGENT, KSK::DEFAULT_USER_AGENT, CRLF);
	message += QString::asprintf("%s", CRLF);

	return message;
}

QString CRtspParser::makeDescribeMethod(const QString&rtspUrl, const int seq)
{
	QString message;

	message += QString::asprintf("%s %s %s%s", RTSP_METHOD_DESCRIBE, rtspUrl.toStdString().c_str(), RTSP_VERSION, CRLF);
	message += QString::asprintf("%s: %d%s", RTSP_HEADER_NAME_CSEQ, seq, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_USER_AGENT, KSK::DEFAULT_USER_AGENT, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_ACCEPT, KSK::DEFAULT_ACCEPT, CRLF);
	message += QString::asprintf("%s", CRLF);

	return message;
}

QString CRtspParser::makeDescribeMethodWithDigest(const QString&rtspUrl, const int seq, const QString& userName, const 
	QString& realm, const QString& nonce, const QString& uri, const QString& response)
{
	QString message;

	message += QString::asprintf("%s %s %s%s", RTSP_METHOD_DESCRIBE, rtspUrl.toStdString().c_str(), RTSP_VERSION, CRLF);
	message += QString::asprintf("%s: %d%s", RTSP_HEADER_NAME_CSEQ, seq, CRLF);
	message += QString::asprintf("%s: %s username=\"%s\", realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\"%s", RTSP_HEADER_NAME_AUTH, RTSP_HEADER_NAME_DIGEST,
		userName.toStdString().c_str(), realm.toStdString().c_str(), nonce.toStdString().c_str(), uri.toStdString().c_str(), response.toStdString().c_str(),CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_USER_AGENT, KSK::DEFAULT_USER_AGENT, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_ACCEPT, KSK::DEFAULT_ACCEPT, CRLF);
	message += QString::asprintf("%s", CRLF);
	
	return message;
}

QString CRtspParser::makeSetupMethod(const QString&rtspUrl, const int seq,const int clientSocketNumber)
{
	QString message;

	message += QString::asprintf("%s %s %s%s", RTSP_METHOD_SETUP, rtspUrl.toStdString().c_str(), RTSP_VERSION, CRLF);
	message += QString::asprintf("%s: %d%s", RTSP_HEADER_NAME_CSEQ, seq, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_USER_AGENT, KSK::DEFAULT_USER_AGENT, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_TRANSPORT, KSK::DEFAULT_TCP_TRASPORT, CRLF);
	//message += QString::asprintf("%s: %sclient_port=%d%s", RTSP_HEADER_NAME_TRANSPORT, KSK::DEFAULT_UDP_TRASPORT,clientSocketNumber ,CRLF);
	message += QString::asprintf("%s", CRLF);

	return message;
}

QString CRtspParser::makePlayMethod(const QString&rtspUrl, const int seq, const QString &sessionId)
{
	QString message;

	message += QString::asprintf("%s %s %s%s", RTSP_METHOD_PLAY, rtspUrl.toStdString().c_str(), RTSP_VERSION, CRLF);
	message += QString::asprintf("%s: %d%s", RTSP_HEADER_NAME_CSEQ, seq, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_USER_AGENT, KSK::DEFAULT_USER_AGENT, CRLF);
	message += QString::asprintf("%s: %s%s", RTSP_HEADER_NAME_SESSION, sessionId.toStdString().c_str(), CRLF);
	message += QString::asprintf("%s: npt=0.000-%s",RTSP_HEADER_NAME_RANGE,CRLF);
	message += QString::asprintf("%s", CRLF);

	return message;
}

QString CRtspParser::parseSdp(const QString& sdp,const QString& rtspUrl)
{
	QString newUrl;
	bool videoFind = false;
	QStringList sdpList = sdp.split("\r\n", QString::SkipEmptyParts);

	for each (QString sdpvalue in sdpList)
	{
		if (sdpvalue.contains("m=video"))
			videoFind = true;

		if (videoFind == true)
		{
			if (sdpvalue.contains("a=control") == false)
				continue;

			QStringList controlInfo = sdpvalue.split("a=control:", QString::SkipEmptyParts);

			if (controlInfo.isEmpty() == false)
			{
				if (controlInfo.at(0).contains("rtsp"))
					newUrl = controlInfo.at(0);
				else
					newUrl = rtspUrl + "/" + controlInfo.at(0);
			}

			break;
		}
	}

	return newUrl;
}

std::map<QString,QString> CRtspParser::rtspResponseMessageParse(const QString&responseMessage)
{
	std::map<QString, QString> headerMap;

	QStringList responseList = responseMessage.split("\r\n\r\n", QString::SkipEmptyParts);

	QStringList headerList = responseList[0].split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
	if (headerList.isEmpty() == true)
		return std::map<QString, QString>();		

	if (headerList.at(0).contains(RTSP_OK) == false)
	{
		if (headerList.at(0).contains(RTSP_UNAUTHORIZED_CODE) == true)
			return rtspUnauthorizedMessageParse(headerList);
		else
			return std::map<QString, QString>();
	}
	   	
	for (int i = 1; i < headerList.size(); ++i)
	{
		QStringList headers = headerList.at(i).split(';', QString::SkipEmptyParts);

		for (int j = 0; j < headers.size(); ++j)
		{
			QStringList temp = headers.at(j).split(QRegExp(":|="));

			if (temp.size() != 2)
				continue;

			QString key = temp[0].replace(" ", "");
			QString value = temp[1].replace(" ", "");
			headerMap[key] = value;
		}
	}

	if (responseList.size() > 1)
		headerMap[RTSP_SDP] = responseList[1];

	return headerMap;
}

std::map<QString, QString> CRtspParser::rtspUnauthorizedMessageParse(const QStringList& responseMessage)
{
	std::map<QString, QString> headerMap;
	headerMap[RTSP_HEADER_ERROR] = RTSP_UNAUTHORIZED_CODE;

	for (int i = 1; i < responseMessage.size(); ++i)
	{
		QStringList parseLine = responseMessage.at(i).split(':', QString::SkipEmptyParts);
		if (parseLine.at(0).contains(RTSP_HEADER_NAME_AURHENTICATE) == false)
			continue;

		QStringList parseAuthenticate = parseLine.at(1).split(QRegExp(",|="));
		for (int j = 0; j < parseAuthenticate.size(); j += 2)
		{
			QString key = parseAuthenticate[j].remove('\"').trimmed();
			QString value = parseAuthenticate[j + 1].remove('\"').trimmed();
			headerMap[key] = value;
		}
	}

	return headerMap;
}

