#include "counter.h"
#include "ui_counter.h"
#include <QLabel>

Counter::Counter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Counter)
{
    ui->setupUi(this);

    // 设置标签永久字体
//        QFont counterFont("Arial", 16);  // 字体+字号
//        counterFont.setBold(true);       // 加粗

        QFont font("Arial", 16, QFont::Bold);
        ui->labelCount->setFont(font);
        ui->labelCount->setAlignment(Qt::AlignCenter);

//    void on_labelCount_linkActivated(const QString &link);

//    void onAddClicked();

//    void onResetClicked();

    connect(ui->bntAdd, &QAbstractButton::clicked, this, &Counter::onAddClicked);

    connect(ui->bntReset, &QAbstractButton::clicked, this, &Counter::onResetClicked);

}

Counter::~Counter()
{
    delete ui;
}

void Counter::onAddClicked()
{
    count ++;
    ui->labelCount->setNum(count);
}

void Counter::onResetClicked()
{
    count = 0;
    ui->labelCount->setNum(count);
}
