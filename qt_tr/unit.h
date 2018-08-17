#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
typedef unsigned int un;
class Unit
{

public:
    Unit(void);
    ~Unit(void);

    void setId(un id);
    void setCode(long code);
    void setBarcode(std::string barcode);
    void setQuantity(int quantity);
    void setPrice(float price);
    void setEcharge(float echarge);
    void setName(std::string name);
    void setSection(std::string);
    void setGroup(std::string);
    void setDescription(std::string);
    void setMinimum(un minimum);
    bool isUah();
    void addSales(int sales);

    un getId();
    un getCode();
    std::string getBarcode();
    int getQuantity();
    float getPrice();
    float getEcharge();
    std::string  getName();
    std::string getSection();
    std::string getGroup();
    std::string getDescription();
    un getMinimum();
    un getSales();

private:
    unsigned id;
    unsigned code;
    std::string barcode;
    int quantity;
    float price;
    float echarge;
    std::string name;
    std::string section;
    std::string group;
    std::string description;
    unsigned minimum;

    std::string removeSpaces(std::string str);
    std::string intToString(int value);
    int stringToInt(std::string str);

    friend std::ostream& operator<<(std::ostream& os, const Unit& );
    friend std::istream& operator>>(std::istream& is,  Unit& );
};


#endif // UNIT_H
