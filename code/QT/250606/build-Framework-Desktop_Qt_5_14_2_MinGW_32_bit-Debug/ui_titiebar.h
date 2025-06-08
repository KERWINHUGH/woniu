/********************************************************************************
** Form generated from reading UI file 'titiebar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITIEBAR_H
#define UI_TITIEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_titiebar
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *bntMin;
    QPushButton *bntMax;
    QPushButton *bntClose;

    void setupUi(QDialog *titiebar)
    {
        if (titiebar->objectName().isEmpty())
            titiebar->setObjectName(QString::fromUtf8("titiebar"));
        titiebar->resize(750, 480);
        gridLayout = new QGridLayout(titiebar);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(titiebar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(25, 25));
        label->setMaximumSize(QSize(25, 25));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(titiebar);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(300, 25));
        label_2->setMaximumSize(QSize(300, 25));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bntMin = new QPushButton(titiebar);
        bntMin->setObjectName(QString::fromUtf8("bntMin"));
        bntMin->setMinimumSize(QSize(25, 25));
        bntMin->setMaximumSize(QSize(25, 25));

        horizontalLayout->addWidget(bntMin);

        bntMax = new QPushButton(titiebar);
        bntMax->setObjectName(QString::fromUtf8("bntMax"));
        bntMax->setMinimumSize(QSize(25, 25));
        bntMax->setMaximumSize(QSize(25, 25));

        horizontalLayout->addWidget(bntMax);

        bntClose = new QPushButton(titiebar);
        bntClose->setObjectName(QString::fromUtf8("bntClose"));
        bntClose->setMinimumSize(QSize(25, 25));
        bntClose->setMaximumSize(QSize(25, 25));

        horizontalLayout->addWidget(bntClose);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(titiebar);

        QMetaObject::connectSlotsByName(titiebar);
    } // setupUi

    void retranslateUi(QDialog *titiebar)
    {
        titiebar->setWindowTitle(QCoreApplication::translate("titiebar", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        bntMin->setText(QString());
        bntMax->setText(QString());
        bntClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class titiebar: public Ui_titiebar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITIEBAR_H
