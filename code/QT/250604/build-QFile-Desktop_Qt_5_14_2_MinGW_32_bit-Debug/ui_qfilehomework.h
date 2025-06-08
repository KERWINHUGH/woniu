/********************************************************************************
** Form generated from reading UI file 'qfilehomework.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFILEHOMEWORK_H
#define UI_QFILEHOMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qfileHomework
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *bntTurnOn;
    QLabel *fileName;
    QTextBrowser *fileContent;

    void setupUi(QWidget *qfileHomework)
    {
        if (qfileHomework->objectName().isEmpty())
            qfileHomework->setObjectName(QString::fromUtf8("qfileHomework"));
        qfileHomework->resize(800, 600);
        layoutWidget = new QWidget(qfileHomework);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 21, 502, 535));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        bntTurnOn = new QPushButton(layoutWidget);
        bntTurnOn->setObjectName(QString::fromUtf8("bntTurnOn"));
        bntTurnOn->setMinimumSize(QSize(100, 25));
        bntTurnOn->setMaximumSize(QSize(100, 25));

        horizontalLayout->addWidget(bntTurnOn);

        fileName = new QLabel(layoutWidget);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setMinimumSize(QSize(390, 25));
        fileName->setMaximumSize(QSize(390, 25));
        fileName->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgb(255, 255, 255);\n"
"font: 12pt \"Arial\";"));
        fileName->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(fileName);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        fileContent = new QTextBrowser(layoutWidget);
        fileContent->setObjectName(QString::fromUtf8("fileContent"));
        fileContent->setMinimumSize(QSize(500, 500));
        fileContent->setMaximumSize(QSize(500, 500));

        gridLayout->addWidget(fileContent, 1, 0, 1, 1);


        retranslateUi(qfileHomework);

        QMetaObject::connectSlotsByName(qfileHomework);
    } // setupUi

    void retranslateUi(QWidget *qfileHomework)
    {
        qfileHomework->setWindowTitle(QCoreApplication::translate("qfileHomework", "qfileHomework", nullptr));
        bntTurnOn->setText(QCoreApplication::translate("qfileHomework", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        fileName->setToolTip(QCoreApplication::translate("qfileHomework", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        fileName->setWhatsThis(QCoreApplication::translate("qfileHomework", "<html><head/><body><p>\346\211\223\345\274\200\346\226\207\344\273\266\347\232\204\345\220\215\345\255\227\345\217\212\350\267\257\345\276\204</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        fileName->setText(QString());
        fileContent->setHtml(QCoreApplication::translate("qfileHomework", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\226\207\344\273\266\345\206\205\345\256\271</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qfileHomework: public Ui_qfileHomework {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFILEHOMEWORK_H
