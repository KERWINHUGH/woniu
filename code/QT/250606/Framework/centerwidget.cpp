#include "centerwidget.h"
#include "ui_centerwidget.h"

centerwidget::centerwidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::centerwidget)
{
    ui->setupUi(this);
}

centerwidget::~centerwidget()
{
    delete ui;
}
