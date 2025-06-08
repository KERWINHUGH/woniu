/********************************************************************************
** Form generated from reading UI file 'rediobutton.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDIOBUTTON_H
#define UI_REDIOBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_redioButton
{
public:
    QRadioButton *radioButton;
    QGroupBox *groupBox;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label;

    void setupUi(QWidget *redioButton)
    {
        if (redioButton->objectName().isEmpty())
            redioButton->setObjectName(QString::fromUtf8("redioButton"));
        redioButton->resize(600, 458);
        radioButton = new QRadioButton(redioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(270, 70, 89, 16));
        groupBox = new QGroupBox(redioButton);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(150, 100, 351, 171));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(110, 130, 191, 16));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(110, 30, 201, 16));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(110, 80, 191, 16));
        label = new QLabel(redioButton);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 280, 301, 141));

        retranslateUi(redioButton);

        QMetaObject::connectSlotsByName(redioButton);
    } // setupUi

    void retranslateUi(QWidget *redioButton)
    {
        redioButton->setWindowTitle(QCoreApplication::translate("redioButton", "redioButton", nullptr));
        radioButton->setText(QCoreApplication::translate("redioButton", "RadioButton", nullptr));
        groupBox->setTitle(QCoreApplication::translate("redioButton", "GroupBox", nullptr));
        radioButton_4->setText(QCoreApplication::translate("redioButton", "RadioButton33333333333333333", nullptr));
        radioButton_2->setText(QCoreApplication::translate("redioButton", "RadioButton11111111111", nullptr));
        radioButton_3->setText(QCoreApplication::translate("redioButton", "RadioButton22222222222222", nullptr));
        label->setText(QCoreApplication::translate("redioButton", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class redioButton: public Ui_redioButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDIOBUTTON_H
