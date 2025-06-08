#include "switcha.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    switchA w;
    w.show();
    return a.exec();
}
