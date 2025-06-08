#ifndef B_H
#define B_H

#include <QDialog>

namespace Ui {
class B;
}

class B : public QDialog
{
    Q_OBJECT

public:
    explicit B(QWidget *parent = nullptr);
    ~B();

signals:
    void display(int);

private:
    Ui::B *ui;
};

#endif // B_H
