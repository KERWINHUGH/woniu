#include "hellowworld.h"
#include "ui_hellowworld.h"
#include <QDebug>

hellowworld::hellowworld(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hellowworld)
{
    ui->setupUi(this);
//    std::cout << "Hellow World!" << std::endl;

    //connect(sender, single, reciever, slot);
    //QT4
    //connect(ui->closeBnt, SIGNAL(clicked()), this, SLOT(onCloseWidget()));
    //QT5
    //connect(ui->closeBnt, &QAbstractButton::cliked, this, &Helloworld::onCloseWidget);
    //lambda
    //connect(ui->closeBnt, &QAbstractButton::clicked, this, &Helloworld::onShowMaxsized);
//    connect(ui->pushButton, &QAbstractButton::clicked, this, [=](){
//        qDebug() << "show maxsized";
//        this->showMaximized();
//    });
    connect(ui->pushButton, &QAbstractButton::clicked, this, [=](){
        qDebug() << "show Minimized";
        this->showMinimized();
    });
}

void hellowworld::onCloseWidget(){
    qDebug() << "close widget";
    this->close();
}

void hellowworld::onShowMaxsized(){
    qDebug() << "show maxsized-------";
    this->showMaximized();
}

hellowworld::~hellowworld()
{
    delete ui;
}

