#ifndef SWITCHB_H
#define SWITCHB_H

#include <QDialog>

namespace Ui {
class switchB;
}

class switchB : public QDialog
{
    Q_OBJECT

public:
    explicit switchB(QWidget *parent = nullptr);
    ~switchB();

private:
    Ui::switchB *ui;
};

#endif // SWITCHB_H
