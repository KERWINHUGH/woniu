#ifndef QFILEHOMEWORK_H
#define QFILEHOMEWORK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class qfileHomework; }
QT_END_NAMESPACE

class qfileHomework : public QWidget
{
    Q_OBJECT

public:
    qfileHomework(QWidget *parent = nullptr);
    ~qfileHomework();

private:
    Ui::qfileHomework *ui;
};
#endif // QFILEHOMEWORK_H
