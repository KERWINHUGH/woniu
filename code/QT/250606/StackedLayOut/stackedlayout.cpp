#include "stackedlayout.h"

stackedLayout::stackedLayout(QWidget *parent) : QWidget(parent) {
    m_pA = new A;
    m_pB = new B;
    m_pC = new C;

    m_pQStackedLayout = new QStackedLayout(this);

    m_pQStackedLayout->addWidget(m_pA);
    m_pQStackedLayout->addWidget(m_pB);
    m_pQStackedLayout->addWidget(m_pC);

    connect(m_pA, &A::display, m_pQStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pB, &B::display, m_pQStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pC, &C::display, m_pQStackedLayout, &QStackedLayout::setCurrentIndex);
}

stackedLayout::~stackedLayout(){

}

