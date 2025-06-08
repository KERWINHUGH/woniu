#include "qfilehomework.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qfileHomework w;
    w.show();
    return a.exec();
}
