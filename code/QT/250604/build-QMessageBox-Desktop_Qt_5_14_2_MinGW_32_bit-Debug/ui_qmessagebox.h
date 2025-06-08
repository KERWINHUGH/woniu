/********************************************************************************
** Form generated from reading UI file 'qmessagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMESSAGEBOX_H
#define UI_QMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMessageBox
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *bntnormal;
    QPushButton *bntmulti;
    QPushButton *bntwarnning;
    QPushButton *bntinfo;
    QPushButton *bntquestion;
    QPushButton *bntcirtical;
    QPushButton *bntaboutqt;
    QPushButton *bntabout;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *QMessageBox)
    {
        if (QMessageBox->objectName().isEmpty())
            QMessageBox->setObjectName(QString::fromUtf8("QMessageBox"));
        QMessageBox->resize(679, 600);
        gridLayout = new QGridLayout(QMessageBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(271, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        bntnormal = new QPushButton(QMessageBox);
        bntnormal->setObjectName(QString::fromUtf8("bntnormal"));
        bntnormal->setMinimumSize(QSize(100, 31));
        bntnormal->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntnormal);

        bntmulti = new QPushButton(QMessageBox);
        bntmulti->setObjectName(QString::fromUtf8("bntmulti"));
        bntmulti->setMinimumSize(QSize(100, 31));
        bntmulti->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntmulti);

        bntwarnning = new QPushButton(QMessageBox);
        bntwarnning->setObjectName(QString::fromUtf8("bntwarnning"));
        bntwarnning->setMinimumSize(QSize(100, 31));
        bntwarnning->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntwarnning);

        bntinfo = new QPushButton(QMessageBox);
        bntinfo->setObjectName(QString::fromUtf8("bntinfo"));
        bntinfo->setMinimumSize(QSize(100, 31));
        bntinfo->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntinfo);

        bntquestion = new QPushButton(QMessageBox);
        bntquestion->setObjectName(QString::fromUtf8("bntquestion"));
        bntquestion->setMinimumSize(QSize(100, 31));
        bntquestion->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntquestion);

        bntcirtical = new QPushButton(QMessageBox);
        bntcirtical->setObjectName(QString::fromUtf8("bntcirtical"));
        bntcirtical->setMinimumSize(QSize(100, 31));
        bntcirtical->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntcirtical);

        bntaboutqt = new QPushButton(QMessageBox);
        bntaboutqt->setObjectName(QString::fromUtf8("bntaboutqt"));
        bntaboutqt->setMinimumSize(QSize(100, 31));
        bntaboutqt->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntaboutqt);

        bntabout = new QPushButton(QMessageBox);
        bntabout->setObjectName(QString::fromUtf8("bntabout"));
        bntabout->setMinimumSize(QSize(100, 31));
        bntabout->setMaximumSize(QSize(100, 31));

        verticalLayout->addWidget(bntabout);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(270, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        retranslateUi(QMessageBox);

        QMetaObject::connectSlotsByName(QMessageBox);
    } // setupUi

    void retranslateUi(QWidget *QMessageBox)
    {
        QMessageBox->setWindowTitle(QCoreApplication::translate("QMessageBox", "QMessageBox", nullptr));
        bntnormal->setText(QCoreApplication::translate("QMessageBox", "bntnormal", nullptr));
        bntmulti->setText(QCoreApplication::translate("QMessageBox", "bntmulti", nullptr));
        bntwarnning->setText(QCoreApplication::translate("QMessageBox", "bntwarnning", nullptr));
        bntinfo->setText(QCoreApplication::translate("QMessageBox", "bntinfo", nullptr));
        bntquestion->setText(QCoreApplication::translate("QMessageBox", "bntquestion", nullptr));
        bntcirtical->setText(QCoreApplication::translate("QMessageBox", "bntcirtical", nullptr));
        bntaboutqt->setText(QCoreApplication::translate("QMessageBox", "bntaboutqt", nullptr));
        bntabout->setText(QCoreApplication::translate("QMessageBox", "bntabout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMessageBox: public Ui_QMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMESSAGEBOX_H
