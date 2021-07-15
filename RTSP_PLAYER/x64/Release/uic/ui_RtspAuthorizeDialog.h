/********************************************************************************
** Form generated from reading UI file 'RtspAuthorizeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTSPAUTHORIZEDIALOG_H
#define UI_RTSPAUTHORIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CRtspAuthorizeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *subjectLabel;
    QFormLayout *formLayout;
    QLabel *userNameLabel;
    QLabel *passwordLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CRtspAuthorizeDialog)
    {
        if (CRtspAuthorizeDialog->objectName().isEmpty())
            CRtspAuthorizeDialog->setObjectName(QString::fromUtf8("CRtspAuthorizeDialog"));
        CRtspAuthorizeDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(CRtspAuthorizeDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        subjectLabel = new QLabel(CRtspAuthorizeDialog);
        subjectLabel->setObjectName(QString::fromUtf8("subjectLabel"));

        verticalLayout->addWidget(subjectLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        userNameLabel = new QLabel(CRtspAuthorizeDialog);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, userNameLabel);

        passwordLabel = new QLabel(CRtspAuthorizeDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        userNameLineEdit = new QLineEdit(CRtspAuthorizeDialog);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, userNameLineEdit);

        passwordLineEdit = new QLineEdit(CRtspAuthorizeDialog);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordLineEdit);


        verticalLayout->addLayout(formLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(CRtspAuthorizeDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(CRtspAuthorizeDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(CRtspAuthorizeDialog);
        QObject::connect(okButton, SIGNAL(clicked()), CRtspAuthorizeDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CRtspAuthorizeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CRtspAuthorizeDialog);
    } // setupUi

    void retranslateUi(QDialog *CRtspAuthorizeDialog)
    {
        CRtspAuthorizeDialog->setWindowTitle(QCoreApplication::translate("CRtspAuthorizeDialog", "RTSP \354\235\270\354\246\235", nullptr));
        subjectLabel->setText(QCoreApplication::translate("CRtspAuthorizeDialog", "\354\240\225\355\231\225\355\225\234 \353\241\234\352\267\270\354\235\270 \354\235\264\353\246\204 \353\260\217 \353\271\204\353\260\200\353\262\210\355\230\270\353\245\274 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224.", nullptr));
        userNameLabel->setText(QCoreApplication::translate("CRtspAuthorizeDialog", "\354\202\254\354\232\251\354\236\220\353\252\205", nullptr));
        passwordLabel->setText(QCoreApplication::translate("CRtspAuthorizeDialog", "\353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        okButton->setText(QCoreApplication::translate("CRtspAuthorizeDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CRtspAuthorizeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CRtspAuthorizeDialog: public Ui_CRtspAuthorizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTSPAUTHORIZEDIALOG_H
