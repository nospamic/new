#ifndef TEXTBUTOR_H
#define TEXTBUTOR_H

#include <QString>

class Textbutor
{
public:
    Textbutor();
    QString cutter(QString str, int size);
    QString makeBarcode(unsigned code);

};

#endif // TEXTBUTOR_H
