#include "MainWindow.h"
#include <QMessageBox>
#include "RtspParser.h"
#include <QCryptographicHash>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	QString id = "admin";
	QString password = "minju0416!Q";
	QString realm = "IP Camera(21592)";
	QString cmd = "DESCRIBE";
	QString url = "rtsp://192.168.83.147:554";
	QString nonce = "6cf40348776d30ea4b40b20d1cec0bdb";

	QString hash1 = id + ":" + realm + ":" + password;	
	QString hash2 = cmd + ":" + url;

	QByteArray hash1_md5 = QCryptographicHash::hash(hash1.toLocal8Bit(),QCryptographicHash::Md5).toHex();	
	QByteArray hash2_md5 = QCryptographicHash::hash(hash2.toLocal8Bit(), QCryptographicHash::Md5).toHex();	

	QString hash3 = hash1_md5 + ":" + nonce + ":"+ hash2_md5;
	QByteArray hash3_md5 = QCryptographicHash::hash(hash3.toLocal8Bit(), QCryptographicHash::Md5).toHex();
	
}

bool CMainWindow::initialize()
{
	CRtspParser::getInstance()->initialize();

	m_urlOpenShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);

	connect(m_urlOpenShortcut, &QShortcut::activated, this, &CMainWindow::onUrlOpenShortcut);
	connect(&m_urlInputDialog, &QDialog::accepted, this, &CMainWindow::onUrlInputDialogAccept);
	
	return true;
}

void CMainWindow::uninitialize()
{
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
		hash1 = m_rtspAuthorizeDialog.getUserName() + ":" + headerMap["realm"] + m_rtspAuthorizeDialog.getPassword();
		hash2 = "DESCRIBE:"+ headerMap["URL"];
		hash3 = QCryptographicHash::hash(hash1.toLocal8Bit(), QCryptographicHash::Md5).toHex() +":"+headerMap["nonce"]+":"+
			QCryptographicHash::hash(hash2.toLocal8Bit(),QCryptographicHash::Md5).toHex();

		QByteArray hash3_md5 = QCryptographicHash::hash(hash3.toLocal8Bit(), QCryptographicHash::Md5).toHex();
	}
	else
	{
		m_pRtspClient->uninitialize();
		m_pRtspClient->deleteLater();
		m_pRtspClient = nullptr;
	}
}