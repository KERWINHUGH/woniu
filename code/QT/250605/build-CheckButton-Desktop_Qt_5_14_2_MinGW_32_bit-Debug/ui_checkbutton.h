/********************************************************************************
** Form generated from reading UI file 'checkbutton.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKBUTTON_H
#define UI_CHECKBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_checkButton
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkBox_2;
    QLabel *label;

    void setupUi(QWidget *checkButton)
    {
        if (checkButton->objectName().isEmpty())
            checkButton->setObjectName(QString::fromUtf8("checkButton"));
        checkButton->resize(800, 600);
        gridLayout = new QGridLayout(checkButton);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_2 = new QCheckBox(checkButton);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 0, 0, 1, 1);

        label = new QLabel(checkButton);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        retranslateUi(checkButton);

        QMetaObject::connectSlotsByName(checkButton);
    } // setupUi

    void retranslateUi(QWidget *checkButton)
    {
        checkButton->setWindowTitle(QCoreApplication::translate("checkButton", "checkButton", nullptr));
        checkBox_2->setText(QCoreApplication::translate("checkButton", "CheckBox", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class checkButton: public Ui_checkButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKBUTTON_H
