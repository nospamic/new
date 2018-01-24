#include <iostream>
#include <conio.h>
#include "Unit.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>

typedef unsigned int un;

std::ostream& operator<<(std::ostream& os, const Unit& un)
{
	os<<
	
	un.id<<" "<<
	un.code<<" "<<
	un.name<<" "<<
	un.price<<" "<<
	un.qantity<<" "<<
	un.echarge<<" "<<
	un.description<<" "<<
	un.section<<" "<<
	un.group<<" "<<
	un.barcode<<" "<<
	un.salesPerMonth<<"\n";
	return os;
}

std::istream& operator>>(std::istream& is,  Unit& un)
{
	is>>
	
	un.id>>
	un.code>>
	un.name>>
	un.price>>
	un.qantity>>
	un.echarge>>
	un.description>>
	un.section>>
	un.group>>
	un.barcode>>
	un.salesPerMonth;
	return is;
}


unsigned objQuantity(char*path)
{
	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
	//!fs.is_open()?exit(0):true;
	unsigned length=0;
	while(true)
	{
		
		Unit h;
		fs>>h;
		if(fs.eof()){break;}else{++length;}
		//std::cout << h <<"  length="<<length<<"\n";
	}
	fs.close();
	std::cout <<"\n"<<length<<"\n";
	return length;
}


Unit * createArr(unsigned size)
{
	Unit *arry=new Unit[size];
	return &arry[0];
}



Unit* fileToArr(char* path)
{
	
	unsigned size = objQuantity(path);
	Unit *arry=new Unit[size];

	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" -->Array \n";

	for(un a=0; a<size; a++)
	{
		fs>>arry[a];
		std::cout<<arry[a];
	}
	fs.close();
	return &arry[0];
}


template <typename T>
void ArrToFile(char* path, T* arry,un length)
{
	
	//std::cout<<length<<"\n";
	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--Array \n";

	for(unsigned a=0; a<length; a++)
	{
		fs<<arry[a];
		//std::cout<<arry[a];
	}
	fs.close();
}


void makeNewDateFile(char*path, un size)
{
	Unit*arry=createArr(size);
	for(un a=0;a<size;a++)
	{
		std::cout<<arry[a];
	}
	ArrToFile(path,arry,size);
}


void printArr(Unit*arry, un size)
{
	std::cout<<"------------Print array. Size:"<<size<<"\n";
	for(un n=0; n<size; n++)
	{
		std::cout<<arry[n];
	}
	std::cout<<"------------ End -----------------\n";
}


void addUnitToFile(char*path, std::string name, float price)
{
	Unit*base=fileToArr(path);
	un size=objQuantity(path);
	un lastId=base[size-1].getId();
	un lastCode=base[size-1].getCode();

	std::fstream fs; 
	fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
	!fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--unit \n";
	
	Unit unit;
	unit.setId(lastId+1);
	unit.setCode(lastCode+1);
	unit.setName(name);
	unit.setPrice(price);
	fs<<unit;
	fs.close();
}



int main()
{
	setlocale (LC_ALL,"Russian");
	system("mode con lines=50 cols=120");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char*path="date.txt";
	//makeNewDateFile(path,1);
	
	//char*path="date.txt";
	
	//addUnitToFile(path,"Самый_five_товар",12.5);
	
	Unit*base=fileToArr(path);
	printArr(base, objQuantity(path));

	//base[0].setName("первый товар");
	//ArrToFile(path, base ,objQuantity(path));
	//std::cout<<"\n"<<objQuantity(path)<<"\n";
	
	
	delete[] base;
	
	system ("pause");
	return 0;
}