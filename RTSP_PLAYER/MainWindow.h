#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::CMainWindowClass ui;
};
