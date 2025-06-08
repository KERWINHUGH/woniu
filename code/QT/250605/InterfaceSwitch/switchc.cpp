#include "switchc.h"
#include "ui_switchc.h"
#include "switcha.h"
#include "switchb.h"

switchC::switchC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::switchC)
{
    ui->setupUi(this);

    connect(ui->bnt_A, &QPushButton::clicked, this, [=](){
       switchA A;

//       this->close();  // 关闭窗口
//       A.exec();     // 模态显示子对话框

       this->hide();
       A.exec();    //阻塞实现模态(放到显示子界面之前)
       //this->show();
    });

    connect(ui->bnt_B, &QPushButton::clicked, this, [=](){
       switchB B;

//       this->close();  // 关闭窗口
//       B.exec();     // 模态显示子对话框

       this->hide();  // 隐藏主窗口
       B.exec();     // 模态显示子对话框
       //this->show();  // 对话框关闭后恢复
    });
}

switchC::~switchC()
{
    delete ui;
}
