#pragma once

#include <QDialog>
#include "ui_urlInputDialog.h"

class UrlInputDialog : public QDialog
{
public:
	UrlInputDialog();
	~UrlInputDialog();

public:
	QString getUrl();

private:
	void initialize();

private slots:
	void lineEditChanged(const QString&);

private:
	Ui::CUrlInputDialog ui;
};