#pragma once
#include <iostream>
#include <string>
#include <fstream>
typedef unsigned int un;
class Unit
{

public:
	Unit(void);
	~Unit(void);

	void setId(un id);
	void setCode(long code);
	void setBarcode(un barcode);
	void setQantity(int qantity);
	void setPrice(float price);
	void setEcharge(float echarge);
	void setName(std::string name);
	void setSection(std::string);
	void setGroup(std::string);
	void setDescription(std::string);
	void setSalesPerMonth(un salesPerMonth);

	un getId();
	un getCode();

private:
	unsigned id;
	unsigned code;
	unsigned barcode;
	int qantity;
	float price;
	float echarge;
	std::string name;
	std::string section;
	std::string group;
	std::string description;
	unsigned salesPerMonth;

	friend std::ostream& operator<<(std::ostream& os, const Unit& );
	friend std::istream& operator>>(std::istream& is,  Unit& );
};

