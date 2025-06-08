#ifndef C_H
#define C_H

#include <QDialog>

namespace Ui {
class C;
}

class C : public QDialog
{
    Q_OBJECT

public:
    explicit C(QWidget *parent = nullptr);
    ~C();

signals:
    void display(int);

private:
    Ui::C *ui;
};

#endif // C_H
