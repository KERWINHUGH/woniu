#include "rediobutton.h"
#include "ui_rediobutton.h"

redioButton::redioButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::redioButton)
{
    ui->setupUi(this);

    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);

    connect(ui->radioButton_2, &QAbstractButton::toggled, this, [=](){
        ui->label->setText(ui->radioButton_2->text());
    });

    connect(ui->radioButton_3, &QAbstractButton::toggled, this, [=](){
        ui->label->setText(ui->radioButton_3->text());
    });

    connect(ui->radioButton_4, &QAbstractButton::toggled, this, [=](){
        ui->label->setText(ui->radioButton_4->text());
    });
}

redioButton::~redioButton()
{
    delete ui;
}

