#ifndef MODELDIALOG_H
#define MODELDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ModelDialog; }
QT_END_NAMESPACE

class ModelDialog : public QDialog
{
    Q_OBJECT

public:
    ModelDialog(QWidget *parent = nullptr);
    ~ModelDialog();

private:
    Ui::ModelDialog *ui;
};
#endif // MODELDIALOG_H
