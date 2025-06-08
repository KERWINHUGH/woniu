#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    connect(ui->btnNormal, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.exec();
    });

    connect(ui->btnMulti,&QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch(ret) {
        case QMessageBox::Save:
            qDebug() << "Save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default:
            qDebug() << "Error";
            break;
        }
    });

    connect(ui->btnWarnning, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        int ret = QMessageBox::warning(this, tr("warning"),
                                       tr("这是一个警告对话框"),
                                       QMessageBox::Save | QMessageBox::Discard
                                           | QMessageBox::Cancel,
                                       QMessageBox::Save);
        switch(ret) {
        case QMessageBox::Save:
            qDebug() << "Save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default:
            qDebug() << "Error";
            break;
        }
    });

    connect(ui->btnInfo, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        int ret = QMessageBox::information(this, tr("information"),
                                       tr("这是一个信息对话框"),
                                       QMessageBox::Save | QMessageBox::Discard
                                           | QMessageBox::Cancel,
                                       QMessageBox::Save);
        switch(ret) {
        case QMessageBox::Save:
            qDebug() << "Save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default:
            qDebug() << "Error";
            break;
        }
    });

    connect(ui->btnQuestion, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        int ret = QMessageBox::question(this, tr("question"),
                                           tr("这是一个问题对话框"),
                                           QMessageBox::Save | QMessageBox::Discard
                                           | QMessageBox::Cancel,
                                           QMessageBox::Save);
        switch(ret) {
        case QMessageBox::Save:
            qDebug() << "Save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default:
            qDebug() << "Error";
            break;
        }
    });

    connect(ui->btnCritical, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        int ret = QMessageBox::critical(this, tr("critical"),
                                        tr("这是一个错误对话框"),
                                            QMessageBox::Save | QMessageBox::Discard
                                            | QMessageBox::Cancel, QMessageBox::Save);
        switch(ret) {
        case QMessageBox::Save:
            qDebug() << "Save";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard";
            break;
        case QMessageBox::Cancel:
            qDebug() << "Cancel";
            break;
        default:
            qDebug() << "Error";
            break;
        }
    });

    connect(ui->btnAboutQt, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QMessageBox::aboutQt(this, tr("关于Qt"));
    });

    connect(ui->btnAbout, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QMessageBox::about(this, tr("about"), tr("这是关于相关的内容"));
    });

    connect(ui->btnOpenFileName, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open Image"),
                                                   "C:/Users/ciyee",
                                                tr("Image Files (*.png)")
                                                /*tr("Image Files (*.png *.jpg *.bmp)")*/);

        qDebug() << fileName;
    });

    connect(ui->btnSaveFileName, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("save txt"),
                                                        "C:/Users/ciyee",
                                                        tr("Image Files (*.txt)"));
        qDebug() << fileName;
    });

    connect(ui->btnInputDialog, &QPushButton::clicked, this, [=](){
        // 弹窗对话框
        QStringList items;
        items << "苹果" << "橙子" << "橘子" << "葡萄" << "香蕉" << "哈密瓜";
        QString item = QInputDialog::getItem(this, "请选择你喜欢的水果", "你最喜欢的水果:", items, 1, false);
        QMessageBox::information(this, "水果", "您最喜欢的水果是: " + item);
    });

    connect(ui->btnProgressDialog, &QPushButton::clicked, this, [=](){
        // 1. 创建进度条对话框窗口对象
        QProgressDialog *progress = new QProgressDialog(
            "正在拷贝数据...", "取消拷贝", 0, 100, this);
        // 2. 初始化并显示进度条窗口
        progress->setWindowTitle("请稍后");
        progress->setWindowModality(Qt::WindowModal);
        progress->show();

        // 3. 更新进度条
        static int value = 0;
        QTimer *timer = new QTimer;
        connect(timer, &QTimer::timeout, this, [=]() {
            progress->setValue(value);
            value++;
            // 当value > 最大值的时候
            if(value > progress->maximum()) {
                timer->stop();
                value = 0;
                delete progress;
                delete timer;
            }
        });

        connect(progress, &QProgressDialog::canceled, this, [=]() {
            timer->stop();
            value = 0;
            delete progress;
            delete timer;
        });

        timer->start(50);
    });
}

Widget::~Widget() {
    delete ui;
}
