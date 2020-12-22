#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

class Convert
{
public:
    QString FromBinToDec(QString);
    QString FromBinToHex(QString);
    QString FromHexToDec(QString);
    QString FromHexToBin(QString);
    QString FromDecToBin(QString);
    QString FromDecToHex(QString);
};

#endif // CONVERT_H