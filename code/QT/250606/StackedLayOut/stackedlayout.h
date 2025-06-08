#ifndef STACKEDLAYOUT_H
#define STACKEDLAYOUT_H

#include <QWidget>
#include "a.h"
#include "b.h"
#include "c.h"
#include "QStackedLayout"


class stackedLayout : public QWidget {
    Q_OBJECT

public:
    stackedLayout(QWidget *parent = nullptr);
    ~stackedLayout();

    A* m_pA;
    B* m_pB;
    C* m_pC;

    QStackedLayout *m_pQStackedLayout;
};
#endif // STACKEDLAYOUT_H
