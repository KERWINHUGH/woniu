#include "statusbar.h"
#include "ui_statusbar.h"

statusbar::statusbar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statusbar)
{
    ui->setupUi(this);
}

statusbar::~statusbar()
{
    delete ui;
}
