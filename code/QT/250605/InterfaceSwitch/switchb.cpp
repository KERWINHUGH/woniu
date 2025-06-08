#include "switchb.h"
#include "ui_switchb.h"
#include "switcha.h"
#include "switchc.h"

switchB::switchB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::switchB)
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

    connect(ui->bnt_C, &QPushButton::clicked, this, [=](){
       switchC C;

//       this->close();  // 关闭窗口
//       C.exec();     // 模态显示子对话框

       this->hide();  // 隐藏主窗口
       C.exec();     // 模态显示子对话框
       //this->show();  // 对话框关闭后恢复
    });
}

switchB::~switchB()
{
    delete ui;
}
