#include "buttons.h"
#include "ui_buttons.h"
#include <QMessageBox>
#include "help.h"

Buttons::Buttons(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Buttons)
{
    ui->setupUi(this);

    initUI();

    connect(m_pActExit, &QAction::triggered, this, [=](){
        this->close();
    });
    connect(m_pActHelp, &QAction::triggered, this, [=](){
        help h;
        h.exec();
    });
    connect(m_pActAbout, &QAction::triggered, this, [=](){
        QMessageBox::aboutQt(this, "AboutQT");
    });
}

void Buttons::initUI()
{
    m_pMenu = new QMenu;

    m_pActExit = new QAction("退出");
    m_pActHelp = new QAction("帮助");
    m_pActAbout = new QAction("关于");

    //使用addAction直接将Action放到Menu中--------方式1
//    m_pMenu->addAction(m_pActExit);
//    m_pMenu->addAction(m_pActHelp);
//    m_pMenu->addAction(m_pActAbout);

    //先用链表将每个使用Action放到链表中，再用addActions直接将链表放到Menu中--------方式2
    QList<QAction *> list;
    list.push_back(m_pActExit);
    list.push_back(m_pActHelp);
    list.push_back(m_pActAbout);

    m_pMenu->addActions(list);

    //最后将Menu放到按钮中
    ui->bntMenu->setMenu(m_pMenu);

}

Buttons::~Buttons()
{
    delete ui;

    //以下如果手动释放，QT中的Object类将不会再帮我们自动释放
    delete m_pMenu;

    delete m_pActExit;
    delete m_pActHelp;
    delete m_pActAbout;
}


