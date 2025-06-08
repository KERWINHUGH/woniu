#ifndef REDIOBUTTON_H
#define REDIOBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class redioButton; }
QT_END_NAMESPACE

class redioButton : public QWidget
{
    Q_OBJECT

public:
    redioButton(QWidget *parent = nullptr);
    ~redioButton();

private:
    Ui::redioButton *ui;
};
#endif // REDIOBUTTON_H
