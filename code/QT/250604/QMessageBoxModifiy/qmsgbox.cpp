#include "qmsgbox.h"
#include "ui_qmsgbox.h"
#include <QMessageBox>
#include <QDebug>

QmsgBox::QmsgBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QmsgBox)
{
    ui->setupUi(this);

    connect(ui->bntnormal, &QPushButton::clicked, this, [=](){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified!");
        msgBox.exec();
    } );

    connect(ui->bntmulti, &QPushButton::clicked, this, [](){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified!");
        msgBox.setInformativeText("Do you want to save your change?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch(ret){
        case QMessageBox::Save:
            qDebug() << "save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default :
            qDebug() << "default";
            break;
        }
    });

    connect(ui->bntwarnning, &QPushButton::clicked, this, [=](){

        int ret =QMessageBox::warning(this, tr("My App"),
                                      tr("The document has been modified!\n"
                                         "Do you want to save your change?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                      QMessageBox::Save );
        switch(ret){
        case QMessageBox::Save:
            qDebug() << "save warnning";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard warnning";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel warnning";
            break;
        default :
            qDebug() << "default warnning";
            break;
        }
    });

    connect(ui->bntinfo, &QPushButton::clicked, this, [=](){

        int ret =QMessageBox::information(this, tr("My App"),
                                      tr("The document has been modified!\n"
                                         "Do you want to save your change?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                      QMessageBox::Save );
        switch(ret){
        case QMessageBox::Save:
            qDebug() << "save information";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard information";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel information";
            break;
        default :
            qDebug() << "default information";
            break;
        }
    });

    connect(ui->bntquestion, &QPushButton::clicked, this, [=](){

        int ret =QMessageBox::question(this, tr("My App"),
                                      tr("The document has been modified!\n"
                                         "Do you want to save your change?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                      QMessageBox::Save );
        switch(ret){
        case QMessageBox::Save:
            qDebug() << "save question";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard question";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel question";
            break;
        default :
            qDebug() << "default question";
            break;
        }
    });

    connect(ui->bntcritical, &QPushButton::clicked, this, [=](){

        int ret =QMessageBox::critical(this, tr("My App"),
                                      tr("The document has been modified!\n"
                                         "Do you want to save your change?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                      QMessageBox::Save );
        switch(ret){
        case QMessageBox::Save:
            qDebug() << "save critical";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard critical";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel critical";
            break;
        default :
            qDebug() << "default critical";
            break;
        }
    });

    connect(ui->bntabout, &QPushButton::clicked, this, [=](){
        QMessageBox::about(this, tr("about"), tr("about information"));
    });

    connect(ui->bntaboutqt, &QPushButton::clicked, this, [=](){
        QMessageBox::aboutQt(this, tr("aboutqt"));
    });
}

QmsgBox::~QmsgBox()
{
    delete ui;
}

