/********************************************************************************
** Form generated from reading UI file 'switchinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHINTERFACE_H
#define UI_SWITCHINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_switchInterface
{
public:
    QLabel *label;
    QPushButton *bnt_B;
    QPushButton *bnt_C;

    void setupUi(QWidget *switchInterface)
    {
        if (switchInterface->objectName().isEmpty())
            switchInterface->setObjectName(QString::fromUtf8("switchInterface"));
        switchInterface->resize(711, 429);
        label = new QLabel(switchInterface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 40, 471, 311));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        bnt_B = new QPushButton(switchInterface);
        bnt_B->setObjectName(QString::fromUtf8("bnt_B"));
        bnt_B->setGeometry(QRect(190, 210, 100, 30));
        bnt_C = new QPushButton(switchInterface);
        bnt_C->setObjectName(QString::fromUtf8("bnt_C"));
        bnt_C->setGeometry(QRect(430, 210, 100, 30));

        retranslateUi(switchInterface);

        QMetaObject::connectSlotsByName(switchInterface);
    } // setupUi

    void retranslateUi(QWidget *switchInterface)
    {
        switchInterface->setWindowTitle(QCoreApplication::translate("switchInterface", "switchInterface", nullptr));
        label->setText(QCoreApplication::translate("switchInterface", "A", nullptr));
        bnt_B->setText(QCoreApplication::translate("switchInterface", "B", nullptr));
        bnt_C->setText(QCoreApplication::translate("switchInterface", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class switchInterface: public Ui_switchInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHINTERFACE_H
