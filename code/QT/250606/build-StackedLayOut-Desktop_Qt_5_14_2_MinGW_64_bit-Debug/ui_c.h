/********************************************************************************
** Form generated from reading UI file 'c.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_H
#define UI_C_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *C)
    {
        if (C->objectName().isEmpty())
            C->setObjectName(QString::fromUtf8("C"));
        C->resize(736, 479);
        label = new QLabel(C);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 637, 220));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(C);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 246, 637, 219));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 30));
        pushButton_3->setMaximumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(pushButton_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        retranslateUi(C);

        QMetaObject::connectSlotsByName(C);
    } // setupUi

    void retranslateUi(QDialog *C)
    {
        C->setWindowTitle(QCoreApplication::translate("C", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("C", "C", nullptr));
        pushButton_3->setText(QCoreApplication::translate("C", "B", nullptr));
        pushButton_4->setText(QCoreApplication::translate("C", "A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C: public Ui_C {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_H
