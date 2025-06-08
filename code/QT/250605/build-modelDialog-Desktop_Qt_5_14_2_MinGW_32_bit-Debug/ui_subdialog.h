/********************************************************************************
** Form generated from reading UI file 'subdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBDIALOG_H
#define UI_SUBDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_subDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QDialog *subDialog)
    {
        if (subDialog->objectName().isEmpty())
            subDialog->setObjectName(QString::fromUtf8("subDialog"));
        subDialog->resize(400, 300);
        gridLayout = new QGridLayout(subDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(subDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(subDialog);

        QMetaObject::connectSlotsByName(subDialog);
    } // setupUi

    void retranslateUi(QDialog *subDialog)
    {
        subDialog->setWindowTitle(QCoreApplication::translate("subDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("subDialog", "\345\255\220\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class subDialog: public Ui_subDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBDIALOG_H
