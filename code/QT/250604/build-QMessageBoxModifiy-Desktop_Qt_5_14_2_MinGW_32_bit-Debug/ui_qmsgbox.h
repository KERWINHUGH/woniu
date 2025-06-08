/********************************************************************************
** Form generated from reading UI file 'qmsgbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMSGBOX_H
#define UI_QMSGBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QmsgBox
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *bntnormal;
    QPushButton *bntmulti;
    QPushButton *bntwarnning;
    QPushButton *bntinfo;
    QPushButton *bntquestion;
    QPushButton *bntcritical;
    QPushButton *bntaboutqt;
    QPushButton *bntabout;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *QmsgBox)
    {
        if (QmsgBox->objectName().isEmpty())
            QmsgBox->setObjectName(QString::fromUtf8("QmsgBox"));
        QmsgBox->resize(800, 600);
        gridLayout = new QGridLayout(QmsgBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(331, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        bntnormal = new QPushButton(QmsgBox);
        bntnormal->setObjectName(QString::fromUtf8("bntnormal"));
        bntnormal->setMinimumSize(QSize(100, 31));
        bntnormal->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntnormal);

        bntmulti = new QPushButton(QmsgBox);
        bntmulti->setObjectName(QString::fromUtf8("bntmulti"));
        bntmulti->setMinimumSize(QSize(100, 31));
        bntmulti->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntmulti);

        bntwarnning = new QPushButton(QmsgBox);
        bntwarnning->setObjectName(QString::fromUtf8("bntwarnning"));
        bntwarnning->setMinimumSize(QSize(100, 31));
        bntwarnning->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntwarnning);

        bntinfo = new QPushButton(QmsgBox);
        bntinfo->setObjectName(QString::fromUtf8("bntinfo"));
        bntinfo->setMinimumSize(QSize(100, 31));
        bntinfo->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntinfo);

        bntquestion = new QPushButton(QmsgBox);
        bntquestion->setObjectName(QString::fromUtf8("bntquestion"));
        bntquestion->setMinimumSize(QSize(100, 31));
        bntquestion->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntquestion);

        bntcritical = new QPushButton(QmsgBox);
        bntcritical->setObjectName(QString::fromUtf8("bntcritical"));
        bntcritical->setMinimumSize(QSize(100, 31));
        bntcritical->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntcritical);

        bntaboutqt = new QPushButton(QmsgBox);
        bntaboutqt->setObjectName(QString::fromUtf8("bntaboutqt"));
        bntaboutqt->setMinimumSize(QSize(100, 31));
        bntaboutqt->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntaboutqt);

        bntabout = new QPushButton(QmsgBox);
        bntabout->setObjectName(QString::fromUtf8("bntabout"));
        bntabout->setMinimumSize(QSize(100, 31));
        bntabout->setMaximumSize(QSize(100, 31));

        verticalLayout_2->addWidget(bntabout);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(331, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        retranslateUi(QmsgBox);

        QMetaObject::connectSlotsByName(QmsgBox);
    } // setupUi

    void retranslateUi(QWidget *QmsgBox)
    {
        QmsgBox->setWindowTitle(QCoreApplication::translate("QmsgBox", "QmsgBox", nullptr));
        bntnormal->setText(QCoreApplication::translate("QmsgBox", "bntnormal", nullptr));
        bntmulti->setText(QCoreApplication::translate("QmsgBox", "bntmulti", nullptr));
        bntwarnning->setText(QCoreApplication::translate("QmsgBox", "bntwarnning", nullptr));
        bntinfo->setText(QCoreApplication::translate("QmsgBox", "bntinfo", nullptr));
        bntquestion->setText(QCoreApplication::translate("QmsgBox", "bntquestion", nullptr));
        bntcritical->setText(QCoreApplication::translate("QmsgBox", "bntcritical", nullptr));
        bntaboutqt->setText(QCoreApplication::translate("QmsgBox", "bntaboutqt", nullptr));
        bntabout->setText(QCoreApplication::translate("QmsgBox", "bntabout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QmsgBox: public Ui_QmsgBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMSGBOX_H
