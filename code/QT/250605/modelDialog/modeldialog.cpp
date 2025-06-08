#include "modeldialog.h"
#include "ui_modeldialog.h"
#include <QDebug>
#include "subdialog.h"

ModelDialog::ModelDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModelDialog)
{
    ui->setupUi(this);

    connect(ui->btnSwitch, &QPushButton::clicked, this, [=](){
        qDebug() << "切换界面";
        //实现模态（模式）------方式1
//        subDialog subdlg;
//        subdlg.exec();    //阻塞实现模态(放到显示子界面之前)
//        subdlg.show();


        //实现模态（模式）------方式2
//        subDialog *m_subdialog = new subDialog;
//        m_subdialog->setModal(true);
//        m_subdialog->show();

        //实现模态（模式）------方式3
//        subDialog *m_subdialog = new subDialog;
//        m_subdialog->setWindowModality(Qt::ApplicationModal);
//        m_subdialog->show();

        //实现模态（模式）------方式4
        subDialog *m_subdialog = new subDialog;
        m_subdialog->setAttribute(Qt::WA_ShowModal);
        m_subdialog->show();

    });
}

ModelDialog::~ModelDialog()
{
    delete ui;
}

