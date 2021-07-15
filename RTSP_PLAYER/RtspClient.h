#pragma once
#include <QObject>
#include <QUrl>
#include <QtNetwork/QTcpSocket>
#include "RtpThread.h"
#include "Define.h"
#include <QTimer>

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
	void onNewFrame(const QByteArray frameData);

private slots:
	void onConneted();
	void onDisconnected();
	void onReceivedData();	
	void onSendRtcp();

private:
	void processRTSP(const QString& rtspMessage);
	void processRTP(const QByteArray& rtpData);

	void processSingleNal(const QByteArray& rtpData);
	void processFU_A(const QByteArray& rtpData);
	void processNewFrame(KSK::ENalUnit nalType);
	
	void requestOptionMethod();
	void requestDescribeMethod();
	void requestSetupMethod();
	void requestPlayMethod();

private:
	QUrl m_rtspUrl;
	QTcpSocket *m_pRtspSocket = nullptr;		
	bool m_bTcp = false;
	unsigned int m_nSEQ = 2;
	unsigned int m_rtcpssrc;
	QString m_sessionId;
	KSK::ERtspState m_rtspState;	

	QByteArray m_buffer;
	QByteArray m_frameBuffer;

	QByteArray m_sps;
	QByteArray m_pps;
	QByteArray m_startCode;
	QTimer *m_pTimer = nullptr;
};
