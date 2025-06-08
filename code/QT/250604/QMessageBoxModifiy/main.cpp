#include "qmsgbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QmsgBox w;
    w.show();
    return a.exec();
}
