#include "rediobutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    redioButton w;
    w.show();
    return a.exec();
}
