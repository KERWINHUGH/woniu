#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class checkButton; }
QT_END_NAMESPACE

class checkButton : public QWidget
{
    Q_OBJECT

public:
    checkButton(QWidget *parent = nullptr);
    ~checkButton();

private:
    Ui::checkButton *ui;
};
#endif // CHECKBUTTON_H
