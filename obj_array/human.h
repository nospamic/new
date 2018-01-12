#pragma once
#include <iostream>
#include <string>
class human
{
public:
	human(char*name);
	human();
	~human(void);
	void setName(std::string name);
	void setAge(int);
	void setweight(int);
	void setMarried(bool);
	std::string getName();
	unsigned getAge();
	unsigned getWeight();
	bool getIsMarried();
	void print();
private:
	unsigned age;
	unsigned weight;
	std::string name;
	bool isMarried;
	
	friend std::ostream& operator<<(std::ostream& os, const human& hum);
	friend std::istream& operator>>(std::istream& is,  human& hum);

};

