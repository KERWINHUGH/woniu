#include "qmessagebox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox w;
    w.show();
    return a.exec();
}
