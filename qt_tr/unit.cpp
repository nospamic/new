#include "unit.h"

Unit::Unit(void)
{


    name = "Noname";
    id = 0;
    code = 100000;
    price = 0.0;
    quantity = 0;
    echarge = 0.0;
    description="No_description";
    section="No_section";
    group="No_group";
    minimum = 1;
    barcode="0000000000000";
}


Unit::~Unit(void)
{
}


void Unit::setId(un id){this->id=id;}
void Unit::setCode(long code){this->code=code;}
void Unit::setBarcode(std::string barcode){this->barcode=removeSpaces(barcode);}
void Unit::setQuantity(int quantity){this->quantity=quantity;}
void Unit::setPrice(float price){this->price=price;}
void Unit::setEcharge(float echarge){this->echarge=echarge;}
void Unit::setName(std::string name){this->name=removeSpaces(name);}
void Unit::setSection(std::string section){this->section=removeSpaces(section);}
void Unit::setGroup(std::string group){this->group=removeSpaces(group);}
void Unit::setDescription(std::string description){this->description=removeSpaces(description);}
void Unit::setMinimum(un minimum){this->minimum = minimum;}


bool Unit::isUah()
{
    if (getDescription().substr(0,1)=="+" || getDescription().substr(0,1)=="#")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Unit::addSales(int sales)
{
    std::string salesStr = intToString(sales);


    if (description.find("?[") > description.size())
    {
        description = description + "_?[" + salesStr + "]";
    }
    else
    {
        sales += getSales();
        un startPos = description.find("?[");
        un endPos = description.find("]",startPos + 2);
        description.erase(startPos, endPos - startPos + 1);
        salesStr = intToString(sales);
        description = description + "?[" + salesStr + "]";

    }
}


un Unit::getId(){return id;}
un Unit::getCode(){return code;}
std::string Unit::getBarcode(){return barcode;}
int Unit::getQuantity(){return quantity;}
float Unit::getPrice(){return price;}
float Unit::getEcharge(){return echarge;}
std::string  Unit::getName(){return name;}
std::string Unit::getSection(){return section;}
std::string Unit::getGroup(){return group;}
std::string Unit::getDescription(){return description;}
un Unit::getMinimum(){return minimum;}

un Unit::getSales()
{
    un result = 0;
    if (description.find("?[") < description.size())
    {
        un startPos = description.find("?[");
        un endPos = description.find("]",startPos + 2);
        std::string value = description.substr(startPos + 2, endPos - startPos - 2);
        result = stringToInt(value);
    }
    return result;
}


std::string Unit::removeSpaces(std::string str)
{
    std::string result="";
    for(un a=0; a<str.size();a++)
    {
        if (str[a]==' ' || str[a]=='\n' || str[a]=='\t') {result.push_back('_');}
        else {result.push_back(str[a]);}
    }
    return result;
}


std::string Unit::intToString(int value)
{
    std::string str;
    std::ostringstream ss;
    ss<<value;
    str=ss.str();
    return str;
}


int Unit::stringToInt(std::string str)
{
    int d=0;
    std::stringstream ss(str);
    ss>>d;
    return d;
}
