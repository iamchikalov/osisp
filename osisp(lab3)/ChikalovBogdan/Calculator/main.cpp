#include <QApplication>
#include "calculconvertor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculConvertor w;
    w.show();
    return a.exec();
}
