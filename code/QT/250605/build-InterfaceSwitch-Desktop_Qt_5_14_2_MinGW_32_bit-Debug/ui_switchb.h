/********************************************************************************
** Form generated from reading UI file 'switchb.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHB_H
#define UI_SWITCHB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_switchB
{
public:
    QLabel *label;
    QPushButton *bnt_C;
    QPushButton *bnt_A;

    void setupUi(QDialog *switchB)
    {
        if (switchB->objectName().isEmpty())
            switchB->setObjectName(QString::fromUtf8("switchB"));
        switchB->resize(750, 450);
        label = new QLabel(switchB);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 80, 471, 311));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        bnt_C = new QPushButton(switchB);
        bnt_C->setObjectName(QString::fromUtf8("bnt_C"));
        bnt_C->setGeometry(QRect(430, 250, 100, 30));
        bnt_A = new QPushButton(switchB);
        bnt_A->setObjectName(QString::fromUtf8("bnt_A"));
        bnt_A->setGeometry(QRect(190, 250, 100, 30));

        retranslateUi(switchB);

        QMetaObject::connectSlotsByName(switchB);
    } // setupUi

    void retranslateUi(QDialog *switchB)
    {
        switchB->setWindowTitle(QCoreApplication::translate("switchB", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("switchB", "B", nullptr));
        bnt_C->setText(QCoreApplication::translate("switchB", "C", nullptr));
        bnt_A->setText(QCoreApplication::translate("switchB", "A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class switchB: public Ui_switchB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHB_H
