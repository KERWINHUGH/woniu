#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class Buttons; }
QT_END_NAMESPACE

class Buttons : public QWidget
{
    Q_OBJECT

public:
    Buttons(QWidget *parent = nullptr);
    ~Buttons();

    void initUI();

private:
    Ui::Buttons *ui;

    QMenu *m_pMenu;
    QAction *m_pActExit;
    QAction *m_pActHelp;
    QAction *m_pActAbout;
};
#endif // BUTTONS_H
