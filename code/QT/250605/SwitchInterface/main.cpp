#include "switchinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    switchInterface w;
    w.show();
    return a.exec();
}
