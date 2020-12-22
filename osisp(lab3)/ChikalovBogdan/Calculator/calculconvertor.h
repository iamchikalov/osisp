#ifndef CALCULCONVERTOR_H
#define CALCULCONVERTOR_H

#include <QMainWindow>
#include <QMap>
#include <QLibrary>
#include <QMessageBox>

#include "helper_class.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CalculConvertor; }
QT_END_NAMESPACE

class CalculConvertor : public QMainWindow
{
    Q_OBJECT

public:
    CalculConvertor(QWidget *parent = nullptr);
    ~CalculConvertor();

private slots:
    void on_FDec_pressed();

    void on_FBin_pressed();

    void on_FHex_pressed();

    void on_SDec_pressed();

    void on_SBin_pressed();

    void on_SHex_pressed();

    void on_ButtonConvert_clicked();

    void on_actionAbout_triggered();

    void on_actionSelectFont_triggered();

private:
    HelperClass convert;

    QLibrary lib_helper;
    QLibrary lib_about;

    Ui::CalculConvertor *ui;

    QMap<QString, bool> FValues;
    QMap<QString, bool> SValues;
};

#endif // CALCULCONVERTOR_H
