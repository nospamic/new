#pragma once
#include <iostream>
class human
{
public:
	human(char*name);
	human();
	~human(void);
	void setAge(int);
	void setweight(int);
	void setMarried(bool);
	char*getName();
	unsigned getAge();
	unsigned getWeight();
	bool getIsMarried();
	void print();
private:
	unsigned age;
	unsigned weight;
	char* name;
	bool isMarried;
	
	friend std::ostream& operator<<(std::ostream& os, const human& hum);
	friend std::istream& operator>>(std::istream& is,  human& hum);

};

