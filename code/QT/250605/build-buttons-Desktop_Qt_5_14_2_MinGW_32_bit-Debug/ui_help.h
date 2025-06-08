/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_help
{
public:
    QGridLayout *gridLayout;
    QLabel *Lab_Help;

    void setupUi(QDialog *help)
    {
        if (help->objectName().isEmpty())
            help->setObjectName(QString::fromUtf8("help"));
        help->resize(400, 300);
        gridLayout = new QGridLayout(help);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Lab_Help = new QLabel(help);
        Lab_Help->setObjectName(QString::fromUtf8("Lab_Help"));
        Lab_Help->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Lab_Help, 0, 0, 1, 1);


        retranslateUi(help);

        QMetaObject::connectSlotsByName(help);
    } // setupUi

    void retranslateUi(QDialog *help)
    {
        help->setWindowTitle(QCoreApplication::translate("help", "Dialog", nullptr));
        Lab_Help->setText(QCoreApplication::translate("help", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class help: public Ui_help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
