#include "RtspAuthorizeDialog.h"

CRtspAuthorizeDialog::CRtspAuthorizeDialog()
{
	ui.setupUi(this);
}

CRtspAuthorizeDialog::~CRtspAuthorizeDialog()
{

}

QString CRtspAuthorizeDialog::getUserName()
{
	return ui.userNameLineEdit->text();
}

QString CRtspAuthorizeDialog::getPassword()
{
	return ui.passwordLineEdit->text();
}
