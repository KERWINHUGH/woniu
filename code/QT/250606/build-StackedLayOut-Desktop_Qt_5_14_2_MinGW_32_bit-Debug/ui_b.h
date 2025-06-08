/********************************************************************************
** Form generated from reading UI file 'b.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_B_H
#define UI_B_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_B
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *B)
    {
        if (B->objectName().isEmpty())
            B->setObjectName(QString::fromUtf8("B"));
        B->resize(737, 481);
        label = new QLabel(B);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 637, 220));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(B);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 256, 637, 219));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(100, 30));
        pushButton_5->setMaximumSize(QSize(100, 30));

        horizontalLayout_3->addWidget(pushButton_5);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(100, 30));

        horizontalLayout_3->addWidget(pushButton_6);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);


        retranslateUi(B);

        QMetaObject::connectSlotsByName(B);
    } // setupUi

    void retranslateUi(QDialog *B)
    {
        B->setWindowTitle(QCoreApplication::translate("B", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("B", "B", nullptr));
        pushButton_5->setText(QCoreApplication::translate("B", "A", nullptr));
        pushButton_6->setText(QCoreApplication::translate("B", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class B: public Ui_B {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_B_H
