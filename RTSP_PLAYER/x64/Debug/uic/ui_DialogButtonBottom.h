/********************************************************************************
** Form generated from reading UI file 'DialogButtonBottom.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBUTTONBOTTOM_H
#define UI_DIALOGBUTTONBOTTOM_H

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

class Ui_urlInputDialog
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

    void setupUi(QDialog *urlInputDialog)
    {
        if (urlInputDialog->objectName().isEmpty())
            urlInputDialog->setObjectName(QString::fromUtf8("urlInputDialog"));
        urlInputDialog->resize(454, 286);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(urlInputDialog->sizePolicy().hasHeightForWidth());
        urlInputDialog->setSizePolicy(sizePolicy);
        urlInputDialog->setSizeGripEnabled(false);
        verticalLayout_2 = new QVBoxLayout(urlInputDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        subjectLabel = new QLabel(urlInputDialog);
        subjectLabel->setObjectName(QString::fromUtf8("subjectLabel"));
        subjectLabel->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(subjectLabel);

        urlInputInfoLabel = new QLabel(urlInputDialog);
        urlInputInfoLabel->setObjectName(QString::fromUtf8("urlInputInfoLabel"));
        urlInputInfoLabel->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(urlInputInfoLabel);

        urlLineEdit = new QLineEdit(urlInputDialog);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));

        verticalLayout_2->addWidget(urlLineEdit);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(urlInputDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(urlInputDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout_2->addLayout(hboxLayout);


        retranslateUi(urlInputDialog);
        QObject::connect(okButton, SIGNAL(clicked()), urlInputDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), urlInputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(urlInputDialog);
    } // setupUi

    void retranslateUi(QDialog *urlInputDialog)
    {
        urlInputDialog->setWindowTitle(QCoreApplication::translate("urlInputDialog", "\353\257\270\353\224\224\354\226\264 \354\227\264\352\270\260", nullptr));
        subjectLabel->setText(QCoreApplication::translate("urlInputDialog", "\353\204\244\355\212\270\354\233\214\355\201\254 \355\224\204\353\241\234\355\206\240\354\275\234", nullptr));
        urlInputInfoLabel->setText(QCoreApplication::translate("urlInputDialog", "\353\204\244\355\212\270\354\233\214\355\201\254 \354\243\274\354\206\214\353\245\274 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224:", nullptr));
        okButton->setText(QCoreApplication::translate("urlInputDialog", "\354\236\254\354\203\235", nullptr));
        cancelButton->setText(QCoreApplication::translate("urlInputDialog", "\354\267\250\354\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class urlInputDialog: public Ui_urlInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBUTTONBOTTOM_H
