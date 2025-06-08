#include "qfilehomework.h"
#include "ui_qfilehomework.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>



qfileHomework::qfileHomework(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::qfileHomework)
{
    ui->setupUi(this);

    connect(ui->bntTurnOn, &QPushButton::clicked, this, [=](){
        // 打开文件对话框
        QString filePath = QFileDialog::getOpenFileName(
            this,
            tr("打开文本文件"),
            "F:/蜗牛",
            tr("文本文件 (*.txt)")
        );

        // 显示文件路径
        ui->fileName->setText(filePath);

        // 读取文件内容
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);

        // 读取并显示文件内容
        QTextStream in(&file);
        ui->fileContent->setText(in.readAll());
        file.close();
    });
}

qfileHomework::~qfileHomework()
{
    delete ui;
}

