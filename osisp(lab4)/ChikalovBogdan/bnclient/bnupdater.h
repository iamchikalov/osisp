#ifndef BNUPDATER_H
#define BNUPDATER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFileInfo>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class BNUpdater; }
QT_END_NAMESPACE

class BNUpdater : public QMainWindow
{
    Q_OBJECT

public:
    BNUpdater(QWidget *parent = nullptr);
    ~BNUpdater();

private slots:
    void socketReady();
    void socketDisconnection();

    void on_connectToServer_clicked();
    void on_download_clicked();
    void on_disconnect_clicked();

private:
    Ui::BNUpdater *ui;
    void createLib();
    QDateTime getLibVersion();

    QTcpSocket* _socket;
    QByteArray _data;

    QJsonDocument _document;
    QJsonParseError _parseError;

    bool _complexData;

    int _requireSize;
    QString _libName;

    QByteArray _libBytes;
};

#endif // BNUPDATER_H