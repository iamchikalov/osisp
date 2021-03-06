#include "helper_class.h"

HelperClass::HelperClass()
{
}

//------------------------------------------------------

QString HelperClass::FromDecToHex(QString value) {
    QString result;
    int hex;
    int val = value.toInt();

    do {
        hex = val % 16;

        if (hex > 9) {
            hex += (int)'A' - 10;
        }
        else  {
            hex += (int)'0';
        }

        result = (char)hex + result;

        val /= 16;
    } while (val);

    return result;
}

QString HelperClass::FromDecToBin(QString value) {
    QString result;
    int val = value.toInt();

    do {
        result = ('0' + (val % 2)) + result;
        val = val / 2;
    } while (val > 0);

    return result;
}

//------------------------------------------------------

QString HelperClass::FromBinToDec(QString value) {
    QString result;
    bool valid;

    int dec = value.toInt(&valid, 2);

    if (valid)
       result.setNum(dec);

    return result;
}

QString HelperClass::FromBinToHex(QString value) {
    QString temp = FromBinToDec(value);

    QString result = FromDecToHex(temp);

    return result;
}

//------------------------------------------------------

QString HelperClass::FromHexToDec(QString value) {
    QString result;

    bool valid;

    int dec = value.toInt(&valid, 16);

    if (valid)
       result.setNum(dec);

    return result;
}

QString HelperClass::FromHexToBin(QString value) {
    QString temp = FromHexToDec(value);

    QString result = FromDecToBin(temp);

    return result;
}