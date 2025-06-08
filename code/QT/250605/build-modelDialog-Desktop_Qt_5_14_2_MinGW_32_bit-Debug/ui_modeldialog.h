/********************************************************************************
** Form generated from reading UI file 'modeldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELDIALOG_H
#define UI_MODELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ModelDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSwitch;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *ModelDialog)
    {
        if (ModelDialog->objectName().isEmpty())
            ModelDialog->setObjectName(QString::fromUtf8("ModelDialog"));
        ModelDialog->resize(500, 400);
        gridLayout = new QGridLayout(ModelDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label = new QLabel(ModelDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(300, 300));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSwitch = new QPushButton(ModelDialog);
        btnSwitch->setObjectName(QString::fromUtf8("btnSwitch"));
        btnSwitch->setMinimumSize(QSize(140, 30));
        btnSwitch->setMaximumSize(QSize(140, 30));

        horizontalLayout->addWidget(btnSwitch);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(ModelDialog);

        QMetaObject::connectSlotsByName(ModelDialog);
    } // setupUi

    void retranslateUi(QDialog *ModelDialog)
    {
        ModelDialog->setWindowTitle(QCoreApplication::translate("ModelDialog", "ModelDialog", nullptr));
        label->setText(QCoreApplication::translate("ModelDialog", "\344\270\273\347\225\214\351\235\242", nullptr));
        btnSwitch->setText(QCoreApplication::translate("ModelDialog", "\350\267\263\350\275\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelDialog: public Ui_ModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELDIALOG_H
