/********************************************************************************
** Form generated from reading UI file 'hellowworld.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOWWORLD_H
#define UI_HELLOWWORLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hellowworld
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *hellowworld)
    {
        if (hellowworld->objectName().isEmpty())
            hellowworld->setObjectName(QString::fromUtf8("hellowworld"));
        hellowworld->resize(800, 600);
        pushButton = new QPushButton(hellowworld);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 300, 75, 23));

        retranslateUi(hellowworld);

        QMetaObject::connectSlotsByName(hellowworld);
    } // setupUi

    void retranslateUi(QWidget *hellowworld)
    {
        hellowworld->setWindowTitle(QCoreApplication::translate("hellowworld", "hellowworld", nullptr));
        pushButton->setText(QCoreApplication::translate("hellowworld", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hellowworld: public Ui_hellowworld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOWWORLD_H
