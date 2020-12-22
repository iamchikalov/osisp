#include "bnupdater.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BNUpdater updater;
    updater.show();
    return app.exec();
}
