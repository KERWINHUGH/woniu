#include "framwork.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Framwork w;
    w.show();
    return a.exec();
}
