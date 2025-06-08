#include "hellowworld.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hellowworld w;
    w.show();
    return a.exec();
}
