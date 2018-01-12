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


//unsigned length(char*path)
//{
//	std::fstream fs; 
//	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
//
//	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<"\n";
//	unsigned length=0;
//	while(true)
//	{
//		human h;
//		fs>>h;
//		length++;
//		if(fs.eof())break;
//		std::cout << h;
//	}
//	fs.close();
//	return length;
//}


int main()
{
	const int LENGTH=5;
	char*path="data_from_astral.txt";
	
	//std::cout<<length(path);

	
	
	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<"\n";




	human *brigade=new human[LENGTH];
	
	for(int a=0; a <LENGTH ; a++)
	{
		brigade[a]=human("Vovan");
		brigade[a].setAge(a+20);
		brigade[a].print();
		//fs<<brigade[a];
	}


	fs.close();
	delete[] brigade;

	std::fstream fs1; 
	fs1.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
	//human h("vasya");
	std::string str="qwertyuiop";
	fs1>>str;
	std::cout<<str;
	system("pause");
	return 0;
}