#ifndef SWITCHC_H
#define SWITCHC_H

#include <QDialog>

namespace Ui {
class switchC;
}

class switchC : public QDialog
{
    Q_OBJECT

public:
    explicit switchC(QWidget *parent = nullptr);
    ~switchC();

private:
    Ui::switchC *ui;
};

#endif // SWITCHC_H
