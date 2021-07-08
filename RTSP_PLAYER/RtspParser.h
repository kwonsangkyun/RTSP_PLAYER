#pragma once

#include <QMutex>
#include <QString>
#include <map>

class CRtspParser
{
private:
	CRtspParser() {}
	~CRtspParser() {}

public:
	CRtspParser(const CRtspParser&) = delete;
	CRtspParser& operator =(const CRtspParser&) = delete;

	static CRtspParser* getInstance()
	{
		if (s_pRtspParser == nullptr)
		{
			static QMutex mutex;

			{
				QMutexLocker mutexLocker(&mutex);

				if (s_pRtspParser == nullptr)
					s_pRtspParser = new CRtspParser;
			}
		}

		return s_pRtspParser;
	}

	void initialize();
	void uninitialize();

	QString makeOptionMethod(const QString&rtspUrl, const int seq);
	QString makeDescribeMethod(const QString&rtspUrl, const int seq);
	QString makeSetupMethod(const QString&rtspUrl, const int seq);
	QString makePlayMethod(const QString&rtspUrl, const int seq, const QString &sessionId);

	std::map<QString, QString> rtspResponseMessageParse(const QString&responseMessage);
	std::map<QString, QString> rtspUnauthorizedMessageParse(const QStringList& responseMessage);

private:
	static CRtspParser* s_pRtspParser;
};