#include "human.h"

human::human()
{
	name="noname";
	age=0;
	weight=0;
	isMarried=false;
}


human::human(char*name)
{
	this->name=name;
	age=0;
	weight=0;
	isMarried=false;

}


human::~human(void)
{
}


void human::setAge(int age){this->age=age;}
void human::setweight(int weight){this->weight=weight;}
void human::setMarried(bool married){this->isMarried=married;}

char*human::getName(){return name;}
unsigned human::getAge(){return age;}
unsigned human::getWeight(){return weight;}
bool human::getIsMarried(){return isMarried;}


void human::print()
{
	std::cout<<name<<"  age-"<<age<<"  weight-"<<weight<<"\n";
}