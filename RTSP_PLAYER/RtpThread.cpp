#include "RtpThread.h"

void CRtpThread::run()
{
	m_pRtpSocket = new QUdpSocket();
	m_pRtpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
	printf("%d %d\n",this->currentThreadId(), m_pRtpSocket->thread()->currentThreadId());
	bool ret= m_pRtpSocket->bind(QHostAddress::AnyIPv4, 0, QAbstractSocket::DontShareAddress);
	
	emit(isUdpSocketBinding(ret, m_pRtpSocket->localPort()));
	//m_pRtpSocket->moveToThread(this);

	QObject::connect(m_pRtpSocket, &QUdpSocket::readyRead, this, &CRtpThread::onReceivedRtpData);

	while (true)
	{
		if (isInterruptionRequested() == true)
			break;
	}
	
	printf("done\n");
	m_pRtpSocket->disconnect();
	m_pRtpSocket->deleteLater();
}

void CRtpThread::onReceivedRtpData()
{
	QHostAddress sender;
	unsigned short port;

	while (m_pRtpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(m_pRtpSocket->pendingDatagramSize());

		printf("bytesAvailable : %d\n", m_pRtpSocket->bytesAvailable());
		m_pRtpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

		//processRTP(datagram);
	}
}
