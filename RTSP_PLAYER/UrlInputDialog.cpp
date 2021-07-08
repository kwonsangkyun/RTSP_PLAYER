#include "UrlInputDialog.h"

UrlInputDialog::UrlInputDialog()
{
	ui.setupUi(this);

	initialize();
}

UrlInputDialog::~UrlInputDialog()
{

}

QString UrlInputDialog::getUrl()
{
	return ui.urlLineEdit->text();
}

void UrlInputDialog::initialize()
{
	ui.okButton->setEnabled(false);
	connect(ui.urlLineEdit, &QLineEdit::textEdited, this, &UrlInputDialog::lineEditChanged);
}

void UrlInputDialog::lineEditChanged(const QString&)
{
	if (ui.urlLineEdit->text().isEmpty())
		ui.okButton->setEnabled(false);
	else
		ui.okButton->setEnabled(true);
}
