/********************************************************************************
** Form generated from reading UI file 'framwork.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMWORK_H
#define UI_FRAMWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Framwork
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *titleBarLayout;
    QHBoxLayout *centerLayout;
    QHBoxLayout *statusBarLayout;

    void setupUi(QWidget *Framwork)
    {
        if (Framwork->objectName().isEmpty())
            Framwork->setObjectName(QString::fromUtf8("Framwork"));
        Framwork->resize(750, 480);
        Framwork->setMinimumSize(QSize(0, 480));
        Framwork->setMaximumSize(QSize(16777215, 493));
        gridLayout = new QGridLayout(Framwork);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        titleBarLayout = new QHBoxLayout();
        titleBarLayout->setSpacing(2);
        titleBarLayout->setObjectName(QString::fromUtf8("titleBarLayout"));
        titleBarLayout->setContentsMargins(-1, -1, -1, 30);

        gridLayout->addLayout(titleBarLayout, 0, 0, 1, 1);

        centerLayout = new QHBoxLayout();
        centerLayout->setSpacing(2);
        centerLayout->setObjectName(QString::fromUtf8("centerLayout"));
        centerLayout->setContentsMargins(-1, -1, -1, 400);

        gridLayout->addLayout(centerLayout, 1, 0, 1, 1);

        statusBarLayout = new QHBoxLayout();
        statusBarLayout->setSpacing(2);
        statusBarLayout->setObjectName(QString::fromUtf8("statusBarLayout"));
        statusBarLayout->setContentsMargins(-1, -1, -1, 30);

        gridLayout->addLayout(statusBarLayout, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 150);
        gridLayout->setRowStretch(2, 10);

        retranslateUi(Framwork);

        QMetaObject::connectSlotsByName(Framwork);
    } // setupUi

    void retranslateUi(QWidget *Framwork)
    {
        Framwork->setWindowTitle(QCoreApplication::translate("Framwork", "Framwork", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Framwork: public Ui_Framwork {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMWORK_H
