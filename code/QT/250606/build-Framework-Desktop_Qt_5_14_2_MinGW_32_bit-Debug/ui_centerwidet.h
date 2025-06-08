/********************************************************************************
** Form generated from reading UI file 'centerwidet.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERWIDET_H
#define UI_CENTERWIDET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_centerwidet
{
public:

    void setupUi(QDialog *centerwidet)
    {
        if (centerwidet->objectName().isEmpty())
            centerwidet->setObjectName(QString::fromUtf8("centerwidet"));
        centerwidet->resize(400, 300);

        retranslateUi(centerwidet);

        QMetaObject::connectSlotsByName(centerwidet);
    } // setupUi

    void retranslateUi(QDialog *centerwidet)
    {
        centerwidet->setWindowTitle(QCoreApplication::translate("centerwidet", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class centerwidet: public Ui_centerwidet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERWIDET_H
