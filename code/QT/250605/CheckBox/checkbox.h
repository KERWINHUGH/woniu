#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class checkBox; }
QT_END_NAMESPACE

class checkBox : public QWidget
{
    Q_OBJECT

public:
    checkBox(QWidget *parent = nullptr);
    ~checkBox();

private:
    Ui::checkBox *ui;
};
#endif // CHECKBOX_H
