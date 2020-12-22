#ifndef LIBWORKER_H
#define LIBWORKER_H

#include <QString>
#include <QDir>
#include <QDateTime>

class libWorker
{
public:
    libWorker();
    ~libWorker();

    QString getLibName();
    QByteArray getLibBytes();
    int getLibSize();
    QDateTime getLibVersion();

private:
    QDir* _libDir;
};

#endif // LIBWORKER_H