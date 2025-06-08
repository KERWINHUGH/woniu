#ifndef HELLOWWORLD_H
#define HELLOWWORLD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class hellowworld; }
QT_END_NAMESPACE

class hellowworld : public QWidget
{
    Q_OBJECT

public:
    hellowworld(QWidget *parent = nullptr);
    ~hellowworld();

public:
    void onCloseWidget();
    void onShowMaxsized();

private:
    Ui::hellowworld *ui;
};
#endif // HELLOWWORLD_H
