#ifndef SWITCHA_H
#define SWITCHA_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class switchA; }
QT_END_NAMESPACE

class switchA : public QDialog
{
    Q_OBJECT

public:
    switchA(QWidget *parent = nullptr);
    ~switchA();

private:
    Ui::switchA *ui;
};
#endif // SWITCHA_H
