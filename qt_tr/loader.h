#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <iostream>
//#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <io.h>
#include "Unit.h"

typedef unsigned int un;



class Loader
{

public:
    Loader(void);
    ~Loader(void);

    unsigned objQuantity();
    Unit* createArr(unsigned size);
    Unit* fileToArr();
    void ArrToFile(Unit* arry, un length);
    void makeNewDateFile(un size);
    void printArr();
    void addUnitToFile(std::string name, float price, int quantity, std::string barcode, std::string description);
    std::string removeSpaces(std::string);
    void edit(un code, std::string barcode, int quantity, float price, float echarge, std::string name, std::string section, std::string group, std::string description, un salesPerMonth);
    Unit getUnit(un code);
    Unit getUnit(std::string barcode);
    Unit* selectFromFile(std::string word, int &size);
    std::string nameByBarcode(std::string barcode);
    un getPosition(un code);
    bool fileExists();
    bool unitExists(un code);
    void delUnit(un code);


private:
    const char*path;



};


#endif // LOADER_H
