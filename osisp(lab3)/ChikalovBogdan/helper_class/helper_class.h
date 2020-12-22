#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#include "helper_class_global.h"

#include <QString>

class HELPER_CLASS_EXPORT HelperClass
{
public:
    HelperClass();
    QString FromBinToDec(QString);
    QString FromBinToHex(QString);
    QString FromHexToDec(QString);
    QString FromHexToBin(QString);
    QString FromDecToBin(QString);
    QString FromDecToHex(QString);
};

#endif // HELPERCLASS_H