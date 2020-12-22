#include <QCoreApplication>
#include "bnserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BNServer server;
    server.startServer();

    return a.exec();
}
