#include "switcha.h"
#include "ui_switcha.h"
#include "switchb.h"
#include "switchc.h"

switchA::switchA(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::switchA)
{
    ui->setupUi(this);

    connect(ui->bnt_B, &QPushButton::clicked, this, [=](){
       switchB B;

//       this->close();  // 关闭窗口
//       B.exec();     // 模态显示子对话框

       this->hide();  // 隐藏主窗口
       B.exec();     // 模态显示子对话框
       //this->show();  // 对话框关闭后恢复
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

switchA::~switchA()
{
    delete ui;
}

