#include "b.h"
#include "ui_b.h"
#include "utils.h"

B::B(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::B)
{
    ui->setupUi(this);

    connect(ui->pushButton_5, &QPushButton::clicked, this, [=](){
        display(INDEX_A);
    });

    connect(ui->pushButton_6, &QPushButton::clicked, this, [=](){
        display(INDEX_C);
    });
}

B::~B()
{
    delete ui;
}
