#ifndef COUNTER_H
#define COUNTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Counter; }
QT_END_NAMESPACE

class Counter : public QWidget
{
    Q_OBJECT

public:
    Counter(QWidget *parent = nullptr);
    ~Counter();

private slots:

    void onAddClicked();

    void onResetClicked();

private:
    Ui::Counter *ui;
    int count = 0;
};
#endif // COUNTER_H
