#include "humanedit.h"

HumanEdit::HumanEdit(unsigned code, QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    QFont evan("EanGnivc",34);
    QRegExp money("[0-9]{1,4}[.]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);

    this->setFixedWidth(400);
    this->code = code;
    if(code < 100000)this->close();
    getFields();



}

HumanEdit::~HumanEdit()
{

}

void HumanEdit::getFields()
{
    Human man = humanloader.getHuman(code);
    name = man.getName();
    tel = man.getTel();
    description = man.getDescription();
    debt = man.getDebt();
    summ = man.getSumm();
    discount = man.getDiscount();
}


void HumanEdit::itsOk()
{

}

