#include "unit.h"

Unit::Unit(void)
{


    name="Noname";
    id=0;
    code=0;
    price=0;
    quantity=0;
    echarge=0;
    description="No_description";
    section="No_section";
    group="No_group";
    salesPerMonth=0;
    barcode="000000000000";
}


Unit::~Unit(void)
{
}


void Unit::setId(un id){this->id=id;}
void Unit::setCode(long code){this->code=code;}
void Unit::setBarcode(std::string barcode){this->barcode=barcode;}
void Unit::setQuantity(int quantity){this->quantity=quantity;}
void Unit::setPrice(float price){this->price=price;}
void Unit::setEcharge(float echarge){this->echarge=echarge;}
void Unit::setName(std::string name){this->name=name;}
void Unit::setSection(std::string section){this->section=section;}
void Unit::setGroup(std::string group){this->group=group;}
void Unit::setDescription(std::string description){this->description=description;}
void Unit::setSalesPerMonth(un salesPerMonth){this->salesPerMonth=salesPerMonth;}


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
un Unit::getSalesPerMonth(){return salesPerMonth;}
