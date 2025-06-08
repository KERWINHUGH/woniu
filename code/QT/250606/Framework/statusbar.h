#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QDialog>

namespace Ui {
class statusbar;
}

class statusbar : public QDialog
{
    Q_OBJECT

public:
    explicit statusbar(QWidget *parent = nullptr);
    ~statusbar();

private:
    Ui::statusbar *ui;
};

#endif // STATUSBAR_H
