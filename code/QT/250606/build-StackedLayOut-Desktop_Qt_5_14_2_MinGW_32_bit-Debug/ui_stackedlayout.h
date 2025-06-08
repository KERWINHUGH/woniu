/********************************************************************************
** Form generated from reading UI file 'stackedlayout.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STACKEDLAYOUT_H
#define UI_STACKEDLAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stackedLayout
{
public:

    void setupUi(QWidget *stackedLayout)
    {
        if (stackedLayout->objectName().isEmpty())
            stackedLayout->setObjectName(QString::fromUtf8("stackedLayout"));
        stackedLayout->resize(641, 413);

        retranslateUi(stackedLayout);

        QMetaObject::connectSlotsByName(stackedLayout);
    } // setupUi

    void retranslateUi(QWidget *stackedLayout)
    {
        stackedLayout->setWindowTitle(QCoreApplication::translate("stackedLayout", "stackedLayout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stackedLayout: public Ui_stackedLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STACKEDLAYOUT_H
