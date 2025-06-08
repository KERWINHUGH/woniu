#include "a.h"
#include "ui_a.h"
#include "utils.h"

A::A(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::A)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        display(INDEX_B);
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){
        display(INDEX_C);
    });
}

A::~A()
{
    delete ui;
}
