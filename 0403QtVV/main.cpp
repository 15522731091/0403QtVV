#include "QtVV.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtVV w;
    w.show();
    return a.exec();
}
