/********************************************************************************
** Form generated from reading UI file 'buttons.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONS_H
#define UI_BUTTONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Buttons
{
public:
    QPushButton *bntMenu;

    void setupUi(QWidget *Buttons)
    {
        if (Buttons->objectName().isEmpty())
            Buttons->setObjectName(QString::fromUtf8("Buttons"));
        Buttons->resize(800, 600);
        bntMenu = new QPushButton(Buttons);
        bntMenu->setObjectName(QString::fromUtf8("bntMenu"));
        bntMenu->setGeometry(QRect(280, 190, 75, 23));

        retranslateUi(Buttons);

        QMetaObject::connectSlotsByName(Buttons);
    } // setupUi

    void retranslateUi(QWidget *Buttons)
    {
        Buttons->setWindowTitle(QCoreApplication::translate("Buttons", "Buttons", nullptr));
        bntMenu->setText(QCoreApplication::translate("Buttons", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Buttons: public Ui_Buttons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONS_H
