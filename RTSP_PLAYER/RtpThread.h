#pragma once

#include <QThread>
#include <QtNetwork/QUdpSocket>

class CRtpThread : public QThread
{
	Q_OBJECT
public:

signals:
	void isUdpSocketBinding(bool isSuccess,int port);

protected:
	void run() override;

private slots:
	void onReceivedRtpData();

private:
	QUdpSocket *m_pRtpSocket = nullptr;
};