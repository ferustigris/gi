#include <QtGui/QApplication>
#include <core.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCore server("", 45450);
    return a.exec();
}
