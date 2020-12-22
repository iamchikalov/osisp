#include "convertor.h"
#include "ui_Convertor.h"
#include <QMap>

Convertor::Convertor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Convertor)
{
    ui->setupUi(this);
    FValues.insert("FDec", false);
    FValues.insert("FBin", false);
    FValues.insert("FHex", false);
    SValues.insert("SDec", false);
    SValues.insert("SBin", false);
    SValues.insert("SHex", false);
}

Convertor::~Convertor()
{
    delete ui;
}

void Convertor::SetFalse(QMap<QString, bool> &map) {
    for (auto i = map.begin(); i != map.end(); ++i) {
        i.value() = false;
    }
}

void Convertor::on_FDec_pressed()
{
    SetFalse(FValues);
    FValues["FDec"] = true;
}

void Convertor::on_FBin_pressed()
{
    SetFalse(FValues);
    FValues["FBin"] = true;
}

void Convertor::on_FHex_pressed()
{
    SetFalse(FValues);
    FValues["FHex"] = true;
}

void Convertor::on_SDec_pressed()
{
    SetFalse(SValues);
    SValues["SDec"] = true;
}

void Convertor::on_SBin_pressed()
{
    SetFalse(SValues);
    SValues["SBin"] = true;
}

void Convertor::on_SHex_pressed()
{
    SetFalse(SValues);
    SValues["SHex"] = true;
}

QString Convertor::FromDecToHex(QString value) {
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

QString Convertor::FromDecToBin(QString value) {
    QString result;
    int val = value.toInt();
    do {
        result = ('0' + (val % 2)) + result;
        val = val / 2;
    } while (val > 0);

    return result;
}

QString Convertor::FromBinToDec(QString value) {
    QString result;
    bool valid;
    int dec = value.toInt(&valid, 2);
    if (valid)
       result.setNum(dec);

    return result;
}

QString Convertor::FromBinToHex(QString value) {
    QString temp = FromBinToDec(value);
    QString result = FromDecToHex(temp);

    return result;
}

QString Convertor::FromHexToDec(QString value) {
    QString result;
    bool valid;
    int dec = value.toInt(&valid, 16);
    if (valid)
       result.setNum(dec);

    return result;
}

QString Convertor::FromHexToBin(QString value) {
    QString temp = FromHexToDec(value);
    QString result = FromDecToBin(temp);

    return result;
}

void Convertor::on_ButtonConvert_clicked()
{
    QString FValue = ui->FInput->text();
    if (FValues["FDec"] == true && SValues["SBin"] == true) {
        ui->SInput->setText(FromDecToBin(FValue));
    }
    if (FValues["FDec"] == true && SValues["SHex"] == true) {
        ui->SInput->setText(FromDecToHex(FValue));
    }
    if (FValues["FBin"] == true && SValues["SDec"] == true) {
        ui->SInput->setText(FromBinToDec(FValue));
    }
    if (FValues["FBin"] == true && SValues["SHex"] == true) {
        ui->SInput->setText(FromBinToHex(FValue));
    }
    if (FValues["FHex"] == true && SValues["SDec"] == true) {
        ui->SInput->setText(FromHexToDec(FValue));
    }
    if (FValues["FHex"] == true && SValues["SBin"] == true) {
        ui->SInput->setText(FromHexToBin(FValue));
    }
}
