#include <stdio.h>
#include <conio.h>
#include "human.h"
#include <Windows.h>
#include <fstream>
#include <string>



std::ostream& operator<<(std::ostream& os, const human& hum)
{
	os<<hum.name<<" "<<hum.age<<" "<<hum.weight<<" "<<hum.isMarried<<"\n";
	return os;
}

std::istream& operator>>(std::istream& is,  human& hum)
{
	is>>hum.name>>hum.age>>hum.weight>>hum.isMarried;
	return is;
}


unsigned objQuantity(char*path)
{
	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

	!fs.is_open()?exit(0):true;
	unsigned length=0;
	while(true)
	{
		human h;
		fs>>h;
		length++;
		if(fs.eof())break;
		//std::cout << h;
	}
	fs.close();
	return length;
}


int main()
{
	//const int LENGTH=5;
	char*path="data_from_astral.txt";
	std::cout<<"\n"<<objQuantity(path)<<"\n";

	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<"\n";


	unsigned length = objQuantity(path);

	human *brigade=new human[length];
	
	for(int a=0; a<length; a++)
	{
		brigade[a]=human("Vovan");
		brigade[a].setAge(a+20);
		//brigade[a].print();
		fs>>brigade[a];
		std::cout<<brigade[a];
	}


	fs.close();
	delete[] brigade;

	system("pause");
	return 0;
}