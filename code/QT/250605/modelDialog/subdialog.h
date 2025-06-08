#ifndef SUBDIALOG_H
#define SUBDIALOG_H

#include <QDialog>

namespace Ui {
class subDialog;
}

class subDialog : public QDialog
{
    Q_OBJECT

public:
    explicit subDialog(QWidget *parent = nullptr);
    ~subDialog();

private:
    Ui::subDialog *ui;
};

#endif // SUBDIALOG_H
