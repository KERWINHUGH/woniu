#include "framwork.h"
#include "ui_framwork.h"

Framwork::Framwork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Framwork)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);   //取消原本的框架结构头

    m_pTitlebar = new titiebar;
    m_pStatusbar = new statusbar;
    m_pCenterwidget = new centerwidget;

    ui->titleBarLayout->addWidget(m_pTitlebar);
    ui->centerLayout->addWidget(m_pCenterwidget);
    ui->statusBarLayout->addWidget(m_pStatusbar);

    connect(m_pTitlebar, &titiebar::signalClose, this, &Framwork::close);
}

Framwork::~Framwork()
{
    delete ui;
}

