#ifndef QMSGBOX_H
#define QMSGBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QmsgBox; }
QT_END_NAMESPACE

class QmsgBox : public QWidget
{
    Q_OBJECT

public:
    QmsgBox(QWidget *parent = nullptr);
    ~QmsgBox();

private:
    Ui::QmsgBox *ui;
};
#endif // QMSGBOX_H
