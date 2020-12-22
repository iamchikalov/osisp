#include "bnupdater.h"
#include "ui_bnupdater.h"

#include <QFile>

BNUpdater::BNUpdater(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BNUpdater)
{
    ui->setupUi(this);

    _socket = nullptr;
    _complexData = false;
}

BNUpdater::~BNUpdater()
{
    delete ui;
}

void BNUpdater::socketDisconnection() {
    _socket->deleteLater();
}

void BNUpdater::socketReady() {
    if (_socket->waitForConnected(500)) {
        _socket->waitForReadyRead(500);

        if (!_complexData) {                     // Read request
            _data = _socket->readAll();
        }

        else {
            _libBytes.append(_socket->readAll());

            ui->logs->insertPlainText("Client is downloading packets..\n");
            qDebug() << "Client is downloading packets..\n";

            ui->logs->insertPlainText("Downloaded Size = " + QString::number(_libBytes.size())
                                      + " Need size = " + QString::number(_requireSize) + "\n");
            qDebug() << "Downloaded Size = " << _libBytes.size() << " Need size = " << _requireSize;

            if (_libBytes.size() == _requireSize) {
                ui->logs->insertPlainText("Client downloads the .dll\n");
                qDebug() << "Client downloads the .dll";

                createLib();

                ui->logs->insertPlainText("Dll is created in File System");
                qDebug() << "Dll is created in File System";

                _libBytes.clear();

                _complexData = false;
            }
        }

        _document = QJsonDocument::fromJson(_data, &_parseError);

        if (_parseError.errorString().toInt() == QJsonParseError::NoError) {
            if (_document.object().value("type").toString() == "connect" && _document.object().value("status").toString() == "yes") {
                QMessageBox::information(this, "Information", "Connection with server is set");

                ui->logs->insertPlainText("Client connects with server\n");
                qDebug() << "Client connects with server";
            }

            else if (_document.object().value("type").toString() == "info" && _document.object().value("resp").toString() == "dll") {

                _requireSize = _document.object().value("size").toInt();

                _libName = _document.object().value("libname").toString();

                QDateTime serverLibVersion = QDateTime::fromString(_document.object().value("version").toString());
                QDateTime currentLibVersion = getLibVersion();

                ui->logs->insertPlainText("Client gets the info (libname, libsize, libversion) from server\n");
                qDebug() << "Client gets the info (libname, libsize, libversion) from server";

                if (serverLibVersion > currentLibVersion) {
                    _complexData = true;

                    _socket->write("{\"type\":\"download\", \"params\":\"dll\"}");
                    _socket->waitForBytesWritten(500);

                    ui->logs->insertPlainText("Client sends a request (download) to server\n");
                    qDebug() << "Client sends a request (download) to server";
                }
                else {
                    ui->logs->insertPlainText("Dll is not needed to updating\n");
                    qDebug() << "Dll is not needed to updating";
                }
            }
        }
        _data.clear();
    }
}  

void BNUpdater::createLib() {
    QFile lib("F:\\Programms\\qt_creator\\Projects\\build-CalculConvertor-Desktop_Qt_5_9_9_MinGW_32bit-Release\\release\\" + _libName);


    if (lib.open(QIODevice::WriteOnly)) {
        lib.write(_libBytes);
    }

    lib.close();
}

QDateTime BNUpdater::getLibVersion() {
    QFileInfo lib("F:\\Programms\\qt_creator\\Projects\\build-CalculConvertor-Desktop_Qt_5_9_9_MinGW_32bit-Release\\release\\" + _libName);

    QDateTime time = lib.lastModified();

    return time;
}

void BNUpdater::on_connectToServer_clicked()
{
    ui->logs->insertPlainText("Client sends a request (connect) to server\n");
    qDebug() << "Client sends a request (connect) to server";

    _socket = new QTcpSocket(this);

    connect(_socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnection()));

    _socket->connectToHost("127.0.0.1", 5555);
}

void BNUpdater::on_download_clicked()   // Getting info about the file and downloading it
{
    ui->logs->insertPlainText("Client sends a request (get info) to server\n");
    qDebug() << "Client sends a request (get info) to server";

    if (_socket != nullptr && _socket->isOpen()) {
        _socket->write("{\"type\":\"recInfo\", \"resp\":\"dll\"}");
        _socket->waitForBytesWritten(500);
    }
    else {
        QMessageBox::information(this, "Information", "Client is not connect to server");
    }
}

void BNUpdater::on_disconnect_clicked() // Disconnection
{
    if (_socket != nullptr) {
        delete _socket;
    }

    _socket = nullptr;

    ui->logs->insertPlainText("\nClient disconnet from server\n");
    qDebug() << "Client disconnet from server";
}
