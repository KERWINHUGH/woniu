#ifndef TITIEBAR_H
#define TITIEBAR_H

#include <QDialog>

namespace Ui {
class titiebar;
}

class titiebar : public QDialog
{
    Q_OBJECT

public:
    explicit titiebar(QWidget *parent = nullptr);
    ~titiebar();

signals:
    void signalClose();

private:
    Ui::titiebar *ui;
};

#endif // TITIEBAR_H
