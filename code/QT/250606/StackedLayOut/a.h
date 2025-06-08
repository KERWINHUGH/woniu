#ifndef A_H
#define A_H

#include <QDialog>

namespace Ui {
class A;
}

class A : public QDialog
{
    Q_OBJECT

public:
    explicit A(QWidget *parent = nullptr);
    ~A();

signals:
    void display(int);

private:
    Ui::A *ui;
};

#endif // A_H
