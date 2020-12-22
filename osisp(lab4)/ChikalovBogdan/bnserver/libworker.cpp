#include "libworker.h"

#include <QDebug>
#include <QCoreApplication>

libWorker::libWorker() {}

libWorker::~libWorker() {}

QString libWorker::getLibName() {
    _libDir = new QDir("F:\\Programms\\qt_creator\\Projects\\build-bnserver-Desktop_Qt_5_9_9_MinGW_32bit-Debug\\debug\\Updates");

    _libDir->setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list = _libDir->entryInfoList();

    QRegExp expr(".*\\.dll");

    auto libInfo = std::find_if(list.begin(), list.end(), [&expr](QFileInfo info){return expr.exactMatch(info.fileName());});

    return libInfo->fileName();
}

QByteArray libWorker::getLibBytes() {
    QByteArray result;

    QFile lib(_libDir->filePath(getLibName()));

    if (lib.open(QIODevice::ReadOnly)){
        result = lib.readAll();
    }

    lib.close();

    return result;
}

int libWorker::getLibSize() {
    _libDir = new QDir("F:\\Programms\\qt_creator\\Projects\\build-bnserver-Desktop_Qt_5_9_9_MinGW_32bit-Debug\\debug\\Updates");

    _libDir->setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list = _libDir->entryInfoList();

    QRegExp expr(".*\\.dll");

    auto libInfo = std::find_if(list.begin(), list.end(), [&expr](QFileInfo info){return expr.exactMatch(info.fileName());});

    return libInfo->size();
}

QDateTime libWorker::getLibVersion() {
    QFileInfo libInfo(_libDir->filePath(getLibName()));

    QDateTime time = libInfo.lastModified();

    return time;
}
