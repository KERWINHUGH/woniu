/********************************************************************************
** Form generated from reading UI file 'counter.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTER_H
#define UI_COUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Counter
{
public:
    QLabel *labelCount;
    QPushButton *bntAdd;
    QPushButton *bntReset;
    QLabel *label;

    void setupUi(QWidget *Counter)
    {
        if (Counter->objectName().isEmpty())
            Counter->setObjectName(QString::fromUtf8("Counter"));
        Counter->resize(800, 600);
        labelCount = new QLabel(Counter);
        labelCount->setObjectName(QString::fromUtf8("labelCount"));
        labelCount->setGeometry(QRect(290, 220, 111, 41));
        labelCount->setFrameShape(QFrame::WinPanel);
        labelCount->setFrameShadow(QFrame::Plain);
        labelCount->setLineWidth(10);
        labelCount->setMidLineWidth(10);
        labelCount->setScaledContents(false);
        bntAdd = new QPushButton(Counter);
        bntAdd->setObjectName(QString::fromUtf8("bntAdd"));
        bntAdd->setGeometry(QRect(240, 280, 91, 41));
        bntReset = new QPushButton(Counter);
        bntReset->setObjectName(QString::fromUtf8("bntReset"));
        bntReset->setGeometry(QRect(360, 280, 91, 41));
        label = new QLabel(Counter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 150, 54, 12));
#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(Counter);

        QMetaObject::connectSlotsByName(Counter);
    } // setupUi

    void retranslateUi(QWidget *Counter)
    {
        Counter->setWindowTitle(QCoreApplication::translate("Counter", "Counter", nullptr));
        labelCount->setText(QCoreApplication::translate("Counter", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">0</span></p></body></html>", nullptr));
        bntAdd->setText(QCoreApplication::translate("Counter", "bntAdd", nullptr));
        bntReset->setText(QCoreApplication::translate("Counter", "bntReset", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Counter: public Ui_Counter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTER_H
