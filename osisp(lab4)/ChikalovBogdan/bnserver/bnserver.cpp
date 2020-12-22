#include "bnserver.h"
#include <QDir>

BNServer::BNServer(){
    _libWorker = new libWorker();
}

BNServer::~BNServer(){}

void BNServer::startServer() {
    qDebug() << "BN Server";

    if (this->listen(QHostAddress::Any, 5555)) {        // adress, from start and port for it
        qDebug() << "Listening..";
    }

    else {
        qDebug() << "Not listening..";
    }
}

void BNServer::incomingConnection(int socketDescriptor) {
    _socket = new QTcpSocket(this);
    _socket->setSocketDescriptor(socketDescriptor);  // set unuque var

    connect(_socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnection()));

    qDebug() << socketDescriptor << " client connected";

    _socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    _socket->waitForBytesWritten(500);
    qDebug() << "Sending to client command {\"type\":\"connect\",\"status\":\"yes\"}";

    qDebug() << "Sending to client connection status = YES";
}

void BNServer::socketReady(){
    _data = _socket->readAll();

    qDebug() << "Data from client: " << _data;

    _document = QJsonDocument::fromJson(_data, &_documentError);

    if (_documentError.errorString().toInt() == QJsonParseError::NoError) {
        if (_document.object().value("type").toString() == "download" && _document.object().value("params").toString() == "dll"){
            // download dll and return to client

            QByteArray libBytes = _libWorker->getLibBytes();

            _socket->write(libBytes);

            qDebug() << "Download .dll and return to client";
            qDebug() << "File size is " << _socket->bytesToWrite();

            _socket->waitForBytesWritten(500);
        }

        else if (_document.object().value("type").toString() == "recInfo" && _document.object().value("resp").toString() == "dll") {
            // check info and return to client

            QString libName = _libWorker->getLibName();
            int libSize = _libWorker->getLibSize();
            QString version = _libWorker->getLibVersion().toString();

            qDebug() << "Get info (name, size, version)";

            QByteArray itog = "{\"type\":\"info\", \"resp\":\"dll\", \"version\":\"" + QByteArray::fromStdString(version.toStdString())
                    + "\", \"libname\":\"" + QByteArray::fromStdString(libName.toStdString())
                    + "\", \"size\":" + QByteArray::number(libSize) + "}";

            qDebug() << "Sending to client command " << QString::fromStdString(itog.toStdString());
            qDebug() << "Sending info (name " <<  libName << " + size " << libSize << " + version " << version << ") and return to client";

            _socket->write(itog);
            _socket->waitForBytesWritten(500);
        }
    }
    _data.clear();
}

void BNServer::socketDisconnection(){
    qDebug() << "Disconnect client";

    _socket->deleteLater();
}
