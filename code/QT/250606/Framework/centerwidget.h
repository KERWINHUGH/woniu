#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QDialog>

namespace Ui {
class centerwidget;
}

class centerwidget : public QDialog
{
    Q_OBJECT

public:
    explicit centerwidget(QWidget *parent = nullptr);
    ~centerwidget();

private:
    Ui::centerwidget *ui;
};

#endif // CENTERWIDGET_H
