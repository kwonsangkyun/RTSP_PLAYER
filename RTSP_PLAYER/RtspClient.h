#pragma once
#include <QObject>
#include <QUrl>
#include <QtNetwork/QTcpSocket>
#include "Define.h"

class CRtspClient : public QObject
{
	Q_OBJECT
public:
	CRtspClient(const QString&rtspUrl,bool isTcp = false);
	~CRtspClient();

	bool initialize();
	void uninitialize();

	void requestDescribeDigest(const QString& userName,const QString& realm,const QString& nonce,const QString& uri,
		const QString& response);
signals:
	void unAuthorizedError(std::map<QString, QString> headerMap);

private slots:
	void onConneted();
	void onDisconnected();
	void onReceivedData();

private:
	void processRTSP(const QString& rtspMessage);
	
	void requestOptionMethod();
	void requestDescribeMethod();
	
private:
	QUrl m_rtspUrl;
	QTcpSocket *m_pRtspSocket = nullptr;	
	bool m_bTcp = false;
	unsigned int m_nSEQ = 2;
	unsigned int m_rtcpssrc;
	KSK::ERtspState m_rtspState;	
};
