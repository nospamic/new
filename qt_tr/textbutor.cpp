#include "textbutor.h"

Textbutor::Textbutor()
{

}

QString Textbutor::cutter(QString str, int size)
{
    if(str.size()>size)
    {
        return str.left(size);
    }
    else
    {
        int add = size - str.size();
        for (int n=0; n<add; n++)
        {
            str = str + " ";
        }
    }
    return str;
}

QString Textbutor::makeBarcode(unsigned code)
{
    QString barcode = "4820000" + QString::number(code);
    return barcode;
}
