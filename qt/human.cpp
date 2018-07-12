#include "human.h"

Human::Human()
{
    code = 100000;
    name = "noname";
    tel = "no_fone";
    description = "no_descr";
    summ = 0.0;
    debt = 0.0;
    discount = 0;
}

void Human::setCode(int code) {this->code = code;}

void Human::setName(std::string name) {this->name = name;}

void Human::setTel(std::string tel) {this->tel = tel;}

void Human::setDescription(std::string description) {this->description = description;}

void Human::setSumm(float summ) {this->summ = summ;}

void Human::setDebt(float debt) {this->debt = debt;}

void Human::setDiscount(int discount) {this->discount = discount;}


int Human::getCode() {return code;}

std::string Human::getName() {return name;}

std::string Human::getTel() {return tel;}

std::string Human::getDescription() {return description;}

float Human::getSumm() {return summ;}

float Human::getDebt() {return debt;}

int Human::getDiscount() {return discount;}
