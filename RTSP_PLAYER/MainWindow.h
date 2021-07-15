#pragma once

#include <QtWidgets/QMainWindow>
#include <QShortcut>
#include "ui_MainWindow.h"
#include "UrlInputDialog.h"
#include "RtspAuthorizeDialog.h"
#include "RtspClient.h"
#include "StreamDecoderThread.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = Q_NULLPTR);

	bool initialize();
	void uninitialize();

private slots:
	void onUrlOpenShortcut();
	void onUrlInputDialogAccept();
	void onRtspUnauthorized(std::map<QString,QString> headerMap);
	void onNewFrame(const QByteArray frameData);
	void onDecodeSuccess(QByteArray decodeFrame);

private:
    Ui::CMainWindowClass ui;	
	QShortcut *m_urlOpenShortcut;
	UrlInputDialog m_urlInputDialog;
	CRtspAuthorizeDialog m_rtspAuthorizeDialog;

	CRtspClient *m_pRtspClient = nullptr;
	CStreamDecoderThread *m_pStreamDecoderThread = nullptr;
};
