#ifndef Convertor_H
#define Convertor_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class Convertor; }
QT_END_NAMESPACE

class Convertor : public QMainWindow
{
    Q_OBJECT

public:
    Convertor(QWidget *parent = nullptr);
    ~Convertor();

private slots:
    void on_FDec_pressed();
    void on_FBin_pressed();
    void on_FHex_pressed();
    void on_SDec_pressed();
    void on_SBin_pressed();
    void on_SHex_pressed();
    void on_ButtonConvert_clicked();

private:
    void SetFalse(QMap<QString, bool>&);

    QString FromBinToDec(QString);
    QString FromBinToHex(QString);
    QString FromHexToDec(QString);
    QString FromHexToBin(QString);
    QString FromDecToBin(QString);
    QString FromDecToHex(QString);

    Ui::Convertor *ui;

    QMap<QString, bool> FValues;
    QMap<QString, bool> SValues;
};
#endif // Convertor_H
