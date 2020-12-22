#ifndef BNSERVER_H
#define BNSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

#include "libworker.h"

class BNServer : public QTcpServer{
    Q_OBJECT
public:
    BNServer();
    ~BNServer();

public slots:
    void startServer();
    void incomingConnection(int cosketDescriptor);      // actions for adding new clients, cosketDescriptor - unique number of creation
    void socketReady();                                 // ready socket to read data
    void socketDisconnection();                         // disconnecting from server

private:
    QTcpSocket* _socket;
    QByteArray _data;            // data for setting in the net

    QJsonDocument _document;
    QJsonParseError _documentError;

    libWorker* _libWorker;
};

#endif // BNSERVER_H
