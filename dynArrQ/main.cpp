#include <QCoreApplication>
#include <iostream>
#include "dynarry.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    DynArry<int> dyn(50,10,0);
    dyn.setElement(5,0,100);


    return a.exec();
}
