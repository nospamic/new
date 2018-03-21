#ifndef TEXTBUTOR_H
#define TEXTBUTOR_H

#include <QString>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <QMessageBox>

class Textbutor
{
public:
    Textbutor();
    QString cutter(QString str, int size);
    QString makeBarcode(unsigned code);
    QString barcodeToEvan(QString barcode);
    QString makeLable(QString name, float price, bool isUah);
    QString makePrice(float price, bool isUah);
    QString getDate();
    QString checkSummGen(QString barcode);
    QString testBarcode13(QString barcode);
    std::string removeSpaces(std::string str);



};

#endif // TEXTBUTOR_H
