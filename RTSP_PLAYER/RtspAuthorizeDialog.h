#pragma once

#include "ui_RtspAuthorizeDialog.h"

class CRtspAuthorizeDialog : public QDialog
{
public:
	CRtspAuthorizeDialog();
	~CRtspAuthorizeDialog();

	QString getUserName();
	QString getPassword();

private:
	Ui::CRtspAuthorizeDialog ui;
};
