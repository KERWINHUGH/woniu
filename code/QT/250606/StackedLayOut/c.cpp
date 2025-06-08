#include "c.h"
#include "ui_c.h"
#include "utils.h"

C::C(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C)
{
    ui->setupUi(this);

    connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){
        display(INDEX_B);
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){
        display(INDEX_A);
    });
}

C::~C()
{
    delete ui;
}
