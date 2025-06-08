#ifndef SWITCHINTERFACE_H
#define SWITCHINTERFACE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class switchInterface; }
QT_END_NAMESPACE

class switchInterface : public QWidget
{
    Q_OBJECT

public:
    switchInterface(QWidget *parent = nullptr);
    ~switchInterface();

private:
    Ui::switchInterface *ui;
};
#endif // SWITCHINTERFACE_H
