/********************************************************************************
** Form generated from reading UI file 'urlInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URLINPUTDIALOG_H
#define UI_URLINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CUrlInputDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *subjectLabel;
    QLabel *urlInputInfoLabel;
    QLineEdit *urlLineEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CUrlInputDialog)
    {
        if (CUrlInputDialog->objectName().isEmpty())
            CUrlInputDialog->setObjectName(QString::fromUtf8("CUrlInputDialog"));
        CUrlInputDialog->resize(454, 286);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CUrlInputDialog->sizePolicy().hasHeightForWidth());
        CUrlInputDialog->setSizePolicy(sizePolicy);
        CUrlInputDialog->setSizeGripEnabled(false);
        verticalLayout_2 = new QVBoxLayout(CUrlInputDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        subjectLabel = new QLabel(CUrlInputDialog);
        subjectLabel->setObjectName(QString::fromUtf8("subjectLabel"));
        subjectLabel->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(subjectLabel);

        urlInputInfoLabel = new QLabel(CUrlInputDialog);
        urlInputInfoLabel->setObjectName(QString::fromUtf8("urlInputInfoLabel"));
        urlInputInfoLabel->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(urlInputInfoLabel);

        urlLineEdit = new QLineEdit(CUrlInputDialog);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));

        verticalLayout_2->addWidget(urlLineEdit);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(CUrlInputDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(CUrlInputDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout_2->addLayout(hboxLayout);


        retranslateUi(CUrlInputDialog);
        QObject::connect(okButton, SIGNAL(clicked()), CUrlInputDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CUrlInputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CUrlInputDialog);
    } // setupUi

    void retranslateUi(QDialog *CUrlInputDialog)
    {
        CUrlInputDialog->setWindowTitle(QCoreApplication::translate("CUrlInputDialog", "\353\257\270\353\224\224\354\226\264 \354\227\264\352\270\260", nullptr));
        subjectLabel->setText(QCoreApplication::translate("CUrlInputDialog", "\353\204\244\355\212\270\354\233\214\355\201\254 \355\224\204\353\241\234\355\206\240\354\275\234", nullptr));
        urlInputInfoLabel->setText(QCoreApplication::translate("CUrlInputDialog", "\353\204\244\355\212\270\354\233\214\355\201\254 \354\243\274\354\206\214\353\245\274 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224:", nullptr));
        okButton->setText(QCoreApplication::translate("CUrlInputDialog", "\354\236\254\354\203\235", nullptr));
        cancelButton->setText(QCoreApplication::translate("CUrlInputDialog", "\354\267\250\354\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CUrlInputDialog: public Ui_CUrlInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLINPUTDIALOG_H
