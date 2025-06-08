#ifndef FRAMWORK_H
#define FRAMWORK_H

#include <QWidget>
#include "titiebar.h"
#include "statusbar.h"
#include "centerwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Framwork; }
QT_END_NAMESPACE

class Framwork : public QWidget
{
    Q_OBJECT

public:
    Framwork(QWidget *parent = nullptr);
    ~Framwork();

private:
    Ui::Framwork *ui;

    titiebar* m_pTitlebar;
    statusbar* m_pStatusbar;
    centerwidget* m_pCenterwidget;

};
#endif // FRAMWORK_H
