/********************************************************************************
** Form generated from reading UI file 'centerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERWIDGET_H
#define UI_CENTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_centerwidget
{
public:

    void setupUi(QDialog *centerwidget)
    {
        if (centerwidget->objectName().isEmpty())
            centerwidget->setObjectName(QString::fromUtf8("centerwidget"));
        centerwidget->resize(750, 480);

        retranslateUi(centerwidget);

        QMetaObject::connectSlotsByName(centerwidget);
    } // setupUi

    void retranslateUi(QDialog *centerwidget)
    {
        centerwidget->setWindowTitle(QCoreApplication::translate("centerwidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class centerwidget: public Ui_centerwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERWIDGET_H
