/********************************************************************************
** Form generated from reading UI file 'switcha.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHA_H
#define UI_SWITCHA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_switchA
{
public:
    QPushButton *bnt_B;
    QLabel *label;
    QPushButton *bnt_C;

    void setupUi(QDialog *switchA)
    {
        if (switchA->objectName().isEmpty())
            switchA->setObjectName(QString::fromUtf8("switchA"));
        switchA->resize(750, 450);
        switchA->setLayoutDirection(Qt::LeftToRight);
        bnt_B = new QPushButton(switchA);
        bnt_B->setObjectName(QString::fromUtf8("bnt_B"));
        bnt_B->setGeometry(QRect(200, 240, 100, 30));
        bnt_B->setLayoutDirection(Qt::RightToLeft);
        label = new QLabel(switchA);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 70, 471, 311));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::RightToLeft);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        bnt_C = new QPushButton(switchA);
        bnt_C->setObjectName(QString::fromUtf8("bnt_C"));
        bnt_C->setGeometry(QRect(440, 240, 100, 30));
        bnt_C->setLayoutDirection(Qt::RightToLeft);
        label->raise();
        bnt_B->raise();
        bnt_C->raise();

        retranslateUi(switchA);

        QMetaObject::connectSlotsByName(switchA);
    } // setupUi

    void retranslateUi(QDialog *switchA)
    {
        switchA->setWindowTitle(QCoreApplication::translate("switchA", "switchA", nullptr));
        bnt_B->setText(QCoreApplication::translate("switchA", "B", nullptr));
        label->setText(QCoreApplication::translate("switchA", "A", nullptr));
        bnt_C->setText(QCoreApplication::translate("switchA", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class switchA: public Ui_switchA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHA_H
