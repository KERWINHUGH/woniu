#include "checkbox.h"
#include "ui_checkbox.h"

checkBox::checkBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::checkBox)
{
    ui->setupUi(this);

//    ui->checkBox_2->setAutoExclusive(true);

    ui->checkBox_2->setTristate(true);  //设置复选功能

    connect(ui->checkBox_2, &QCheckBox::checkState, this, [=](Qt::CheckState state){
        switch(state){
        case Qt::CheckState::Unchecked:
            ui->label->setText("Unchecked");
        break;
        case Qt::CheckState::PartiallyChecked:
            ui->label->setText("PartiallyChecked");
        break;
        case Qt::CheckState::Checked:
            ui->label->setText("Checked");
        break;
        }
    });
}

checkBox::~checkBox()
{
    delete ui;
}

