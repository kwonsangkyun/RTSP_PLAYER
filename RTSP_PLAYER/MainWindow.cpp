#include "MainWindow.h"
#include <QMessageBox>
#include "RtspParser.h"
#include <QCryptographicHash>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

bool CMainWindow::initialize()
{
	CRtspParser::getInstance()->initialize();

	m_urlOpenShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);

	connect(m_urlOpenShortcut, &QShortcut::activated, this, &CMainWindow::onUrlOpenShortcut);
	connect(&m_urlInputDialog, &QDialog::accepted, this, &CMainWindow::onUrlInputDialogAccept);
	
	m_pStreamDecoderThread = new CStreamDecoderThread;
	connect(m_pStreamDecoderThread, &CStreamDecoderThread::onDecodeSuccess, this, &CMainWindow::onDecodeSuccess);
	m_pStreamDecoderThread->start();

	return true;
}

void CMainWindow::uninitialize()
{
	if (m_pStreamDecoderThread != nullptr)
	{
		m_pStreamDecoderThread->requestInterruption();
		m_pStreamDecoderThread->wait();
		m_pStreamDecoderThread->deleteLater();
		m_pStreamDecoderThread = nullptr;
	}

	if (m_urlOpenShortcut != nullptr)
	{
		m_urlOpenShortcut->deleteLater();
		m_urlOpenShortcut = nullptr;
	}

	CRtspParser::getInstance()->uninitialize();
}

void CMainWindow::onUrlOpenShortcut()
{
	m_urlInputDialog.show();
}

void CMainWindow::onUrlInputDialogAccept()
{
	QString rtspUrl = m_urlInputDialog.getUrl();

	if (m_pRtspClient != nullptr)
	{
		m_pRtspClient->uninitialize();
		m_pRtspClient->deleteLater();
	}

	m_pRtspClient = new CRtspClient(rtspUrl,false);
	connect(m_pRtspClient, &CRtspClient::unAuthorizedError, this, &CMainWindow::onRtspUnauthorized);
	connect(m_pRtspClient, &CRtspClient::onNewFrame, this, &CMainWindow::onNewFrame);

	if (m_pRtspClient->initialize() == false)
	{
		m_pRtspClient->deleteLater();
		m_pRtspClient = nullptr;

		QMessageBox::critical(this, QString::fromLocal8Bit("오류"), QString::fromLocal8Bit("RTSP 연결에 실패 하였습니다. URL을 다시 확인하세요"));
	}
}

void CMainWindow::onRtspUnauthorized(std::map<QString, QString> headerMap)
{
	if (m_pRtspClient == nullptr)
		return;
	
	QString hash1, hash2, hash3;

	if (m_rtspAuthorizeDialog.exec() == QDialog::Accepted)
	{
		hash1 = m_rtspAuthorizeDialog.getUserName() + ":" + headerMap["Digest realm"] +":"+ m_rtspAuthorizeDialog.getPassword();
		hash2 = "DESCRIBE:"+ headerMap["URL"];
		hash3 = QCryptographicHash::hash(hash1.toLocal8Bit(), QCryptographicHash::Md5).toHex() +":"+headerMap["nonce"]+":"+
			QCryptographicHash::hash(hash2.toLocal8Bit(),QCryptographicHash::Md5).toHex();

		QByteArray hash3_md5 = QCryptographicHash::hash(hash3.toLocal8Bit(), QCryptographicHash::Md5).toHex();

		m_pRtspClient->requestDescribeDigest(m_rtspAuthorizeDialog.getUserName(), headerMap["Digest realm"],
			headerMap["nonce"], headerMap["URL"],hash3_md5);
	}
	else
	{
		m_pRtspClient->uninitialize();
		m_pRtspClient->deleteLater();
		m_pRtspClient = nullptr;
	}
}

void CMainWindow::onNewFrame(const QByteArray frameData)
{
	if (m_pStreamDecoderThread == nullptr)
		return;

	m_pStreamDecoderThread->push(frameData);
}

void CMainWindow::onDecodeSuccess(QByteArray decodeFrame)
{
	QImage image((uchar*)decodeFrame.data(),1920, 1080, QImage::Format_Grayscale8);
	
	ui.lb_video->setPixmap(QPixmap::fromImage(image).scaled(ui.lb_video->width(), ui.lb_video->height(), Qt::KeepAspectRatio));		
}
