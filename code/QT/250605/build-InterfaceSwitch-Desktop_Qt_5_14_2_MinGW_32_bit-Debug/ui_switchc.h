/********************************************************************************
** Form generated from reading UI file 'switchc.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHC_H
#define UI_SWITCHC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_switchC
{
public:
    QPushButton *bnt_A;
    QPushButton *bnt_B;
    QLabel *label;

    void setupUi(QDialog *switchC)
    {
        if (switchC->objectName().isEmpty())
            switchC->setObjectName(QString::fromUtf8("switchC"));
        switchC->resize(750, 450);
        bnt_A = new QPushButton(switchC);
        bnt_A->setObjectName(QString::fromUtf8("bnt_A"));
        bnt_A->setGeometry(QRect(400, 250, 100, 30));
        bnt_B = new QPushButton(switchC);
        bnt_B->setObjectName(QString::fromUtf8("bnt_B"));
        bnt_B->setGeometry(QRect(160, 250, 100, 30));
        label = new QLabel(switchC);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 80, 471, 311));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        label->raise();
        bnt_A->raise();
        bnt_B->raise();

        retranslateUi(switchC);

        QMetaObject::connectSlotsByName(switchC);
    } // setupUi

    void retranslateUi(QDialog *switchC)
    {
        switchC->setWindowTitle(QCoreApplication::translate("switchC", "Dialog", nullptr));
        bnt_A->setText(QCoreApplication::translate("switchC", "A", nullptr));
        bnt_B->setText(QCoreApplication::translate("switchC", "B", nullptr));
        label->setText(QCoreApplication::translate("switchC", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class switchC: public Ui_switchC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHC_H
