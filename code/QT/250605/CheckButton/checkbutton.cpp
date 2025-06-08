#include "checkbutton.h"
#include "ui_checkbutton.h"

checkButton::checkButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::checkButton)
{
    ui->setupUi(this);

//    ui->checkBox_2->setAutoExclusive(true);

    ui->checkBox_2->setTristate(true);  //设置复选功能

    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, [this](int state){
        Qt::CheckState checkstate = static_cast<Qt::CheckState>(state);
        switch(checkstate){
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

checkButton::~checkButton()
{
    delete ui;
}

