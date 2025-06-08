#ifndef QMESSAGEBOX_H
#define QMESSAGEBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QMessageBox; }
QT_END_NAMESPACE

class QMessageBox : public QWidget
{
    Q_OBJECT

public:
    QMessageBox(QWidget *parent = nullptr);
    ~QMessageBox();

private:
    Ui::QMessageBox *ui;
};
#endif // QMESSAGEBOX_H
