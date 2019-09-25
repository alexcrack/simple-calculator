#include "calcdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcDialog w;
    w.show();
    return a.exec();
}
