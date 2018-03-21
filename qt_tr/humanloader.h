#ifndef HUMANLOADER_H
#define HUMANLOADER_H

#include <human.h>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <io.h>


class HumanLoader
{
public:
    HumanLoader();
    ~HumanLoader();
    unsigned size;
    Human *base;
    void delHuman(int code);
    bool existsHuman(int code);
    void addHuman(std::string name, std::string tel, std::string description, int discount);
    Human getHuman(int code);
    void loadBase();



private:
    const char * path;
    const char * reservPath;
    void saveBase();
    void saveReserv();
    unsigned getSize();

};

#endif // HUMANLOADER_H
