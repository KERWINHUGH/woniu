#include "qmessagebox.h"
#include "ui_qmessagebox.h"
#include <QMessageBox>

QMessageBox::QMessageBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QMessageBox)
{
    ui->setupUi(this);

//    connect(ui->bntnormal, &QPushButton::clicked, this, [=](){
//        QMessageBox msgBox;
//        msgBox.text();
//        msgBox.exec();
//    } );

    connect(ui->bntmulti, &QPushButton::clicked, this, [=](){

    });
}

QMessageBox::~QMessageBox()
{
    delete ui;
}

