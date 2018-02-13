#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <iostream>
//#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Unit.h"

typedef unsigned int un;



class Loader
{

public:
    Loader(void);
    ~Loader(void);

    unsigned objQuantity(char*path);
    Unit* createArr(unsigned size);
    Unit* fileToArr(char*path);
    void ArrToFile(char*path, Unit* arry, un length);
    void makeNewDateFile(char*path, un size);
    void printArr();
    void addUnitToFile(char*path, std::string name, float price, int qantity);
    std::string removeSpaces(std::string);
    void edit(un code, un barcode, int qantity, float price, float echarge, std::string name, std::string section, std::string group, std::string description, un salesPerMonth);
    Unit getUnit(un code);

private:
    char*path;



};


#endif // LOADER_H
