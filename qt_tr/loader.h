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
    Unit* fileToArr(char* path);
    void ArrToFile(char* path, Unit* arry,un length);
    void makeNewDateFile(char*path, un size);
    void printArr();
    void addUnitToFile(char*path, std::string name, float price, int qantity);
    std::string removeSpaces(std::string);


private:



};


#endif // LOADER_H
