/********************************************************************************
** Form generated from reading UI file 'statusbar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBAR_H
#define UI_STATUSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_statusbar
{
public:
    QLabel *label;

    void setupUi(QDialog *statusbar)
    {
        if (statusbar->objectName().isEmpty())
            statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->resize(750, 480);
        label = new QLabel(statusbar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 190, 750, 25));
        label->setMinimumSize(QSize(750, 25));
        label->setMaximumSize(QSize(750, 25));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));

        retranslateUi(statusbar);

        QMetaObject::connectSlotsByName(statusbar);
    } // setupUi

    void retranslateUi(QDialog *statusbar)
    {
        statusbar->setWindowTitle(QCoreApplication::translate("statusbar", "Dialog", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class statusbar: public Ui_statusbar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBAR_H
