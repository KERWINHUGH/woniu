#include "switchinterface.h"
#include "ui_switchinterface.h"
#include "switchb.h"
#include "switchc.h"

switchInterface::switchInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::switchInterface)
{
    ui->setupUi(this);

     connect(ui->bnt_B, &QPushButton::clicked, this, [=](){
        switchB B;
//        this->close();
//        B.exec();    //阻塞实现模态(放到显示子界面之前)
//        B.show();

        this->hide();  // 隐藏主窗口
        B.exec();     // 模态显示子对话框
        this->show();  // 对话框关闭后恢复
     });

     connect(ui->bnt_C, &QPushButton::clicked, this, [=](){
        switchC C;
//        this->close();
//        C.exec();    //阻塞实现模态(放到显示子界面之前)
//        C.show();

        this->hide();  // 隐藏主窗口
        C.exec();     // 模态显示子对话框
        this->show();  // 对话框关闭后恢复
     });
}

switchInterface::~switchInterface()
{
    delete ui;
}

