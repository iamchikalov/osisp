#include "calculconvertor.h"
#include "ui_calculconvertor.h"
#include <QLabel>
#include <QFontDialog>
#include <QSettings>

typedef void ( *SetF )( QMap<QString, bool> &);
typedef void ( *SetLN )( QLabel & );
typedef void ( *SetLS )( QLabel & );

CalculConvertor::CalculConvertor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculConvertor)
{
    ui->setupUi(this);

    FValues.insert("FDec", false);
    FValues.insert("FBin", false);
    FValues.insert("FHex", false);

    SValues.insert("SDec", false);
    SValues.insert("SBin", false);
    SValues.insert("SHex", false);

    lib_helper.setFileName( "helper.dll" );
}

CalculConvertor::~CalculConvertor()
{
    delete ui;
}

//------------------------------------------------------

void CalculConvertor::on_FDec_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( FValues );
        }

        FValues["FDec"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

void CalculConvertor::on_FBin_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( FValues );
        }

        FValues["FBin"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

void CalculConvertor::on_FHex_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( FValues );
        }

        FValues["FHex"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

void CalculConvertor::on_SDec_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( SValues );
        }

        SValues["SDec"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

void CalculConvertor::on_SBin_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( SValues );
        }

        SValues["SBin"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

void CalculConvertor::on_SHex_pressed()
{
    if( lib_helper.load() ) {
        SetF setFalse = ( SetF ) lib_helper.resolve( "SetFalse" );
        if( setFalse ) {
            setFalse( SValues );
        }

        SValues["SHex"] = true;

        SetLN setLabN = ( SetLN ) lib_helper.resolve( "SetLabN" );
        if( setLabN ) {
            setLabN( *ui->SuccessLabel );
        }
    }
}

//------------------------------------------------------

void CalculConvertor::on_ButtonConvert_clicked()
{
    QString FValue = ui->FInput->text();

    if (FValues["FDec"] == true && SValues["SBin"] == true) {
        ui->SInput->setText(convert.FromDecToBin(FValue));
    }
    if (FValues["FDec"] == true && SValues["SHex"] == true) {
        ui->SInput->setText(convert.FromDecToHex(FValue));
    }

    if (FValues["FBin"] == true && SValues["SDec"] == true) {
        ui->SInput->setText(convert.FromBinToDec(FValue));
    }
    if (FValues["FBin"] == true && SValues["SHex"] == true) {
        ui->SInput->setText(convert.FromBinToHex(FValue));
    }

    if (FValues["FHex"] == true && SValues["SDec"] == true) {
        ui->SInput->setText(convert.FromHexToDec(FValue));
    }
    if (FValues["FHex"] == true && SValues["SBin"] == true) {
        ui->SInput->setText(convert.FromHexToBin(FValue));
    }

    if(FValues["FDec"] == true && SValues["SDec"] == true) {
        ui->SInput->setText(FValue);
    }
    if(FValues["FBin"] == true && SValues["SBin"] == true){
        ui->SInput->setText(FValue);
    }
    if(FValues["FHex"] == true && SValues["SHex"] == true){
        ui->SInput->setText(FValue);
    }

    if( lib_helper.load() ) {
        SetLS setLabS = ( SetLS ) lib_helper.resolve( "SetLabS" );
        if( setLabS ) {
            setLabS( *ui->SuccessLabel );
        }
    }
}

//------------------------------------------------------

void CalculConvertor::on_actionAbout_triggered()
{
    static QString suffix = "";

    #ifdef QT_DEBUG
        suffix = "d";
    #endif

    static const QString LIB_NAME = "about" + suffix;

    lib_about.setFileName( LIB_NAME );
    typedef void ( *About )( QMainWindow * );
    if( lib_about.load() ) {
        About about = ( About ) lib_about.resolve( "about" );
        if( about ) {
            about( this );
        }
    }
}

void CalculConvertor::on_actionSelectFont_triggered()
{
    bool Changed;
    QFont newFont = QFontDialog::getFont(&Changed);
    if (Changed) {
        ui->ButtonConvert->setFont(newFont);

        ui->menubar->setFont(newFont);

        ui->menuSettings->setFont(newFont);

        ui->FValue->setFont(newFont);
        ui->SValue->setFont(newFont);

        ui->groupBox->setFont(newFont);
        ui->groupBox_2->setFont(newFont);

        ui->FInput->setFont(newFont);
        ui->SInput->setFont(newFont);

        ui->SuccessLabel->setFont(newFont);

        QSettings settings(this);
        settings.setValue("VIEWF", newFont);
    }
}
