#include "titiebar.h"
#include "ui_titiebar.h"

titiebar::titiebar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::titiebar)
{
    ui->setupUi(this);

    connect(ui->bntClose, &QPushButton::clicked, this, [=](){
        emit signalClose();
    });
}

titiebar::~titiebar()
{
    delete ui;
}
