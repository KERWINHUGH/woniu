#include "switchc.h"
#include "ui_switchc.h"
#include "switchb.h"
#include "switchinterface.h"

switchC::switchC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::switchC)
{
    ui->setupUi(this);

    connect(ui->bnt_A, &QPushButton::clicked, this, [=](){
       switchInterface A;
       this->hide();
//       A.exec();    //阻塞实现模态(放到显示子界面之前)
//       A.show();
    });

    connect(ui->bnt_B, &QPushButton::clicked, this, [=](){
       switchB B;
//       this->close();
//       B.exec();    //阻塞实现模态(放到显示子界面之前)
//       B.show();

       this->hide();  // 隐藏主窗口
       B.exec();     // 模态显示子对话框
       this->show();  // 对话框关闭后恢复
    });
}

switchC::~switchC()
{
    delete ui;
}
