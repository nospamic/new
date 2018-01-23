#include "console_tools.h"


void setCur(int x, int y) 
{ 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}


void setColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void namedFrame(char *name, int xPos, int yPos, unsigned xSize, unsigned ySize)
{
	setColor(15,1);
	
	setCur(xPos,yPos);std::cout<<char(213);
	for(unsigned i=0; i<xSize-2;i++){std::cout<<char(205);}
	std::cout<<char(184);

	for(unsigned y=yPos+1; y<yPos+ySize-1;y++)
	{
		setCur(xPos,y);std::cout<<char(179);
		for(unsigned n=0;n<xSize-2;n++){std::cout<<" ";}
		std::cout<<char(179);
	}

	setCur(xPos,yPos+ySize-1);std::cout<<char(212);
	for(unsigned i=0; i<xSize-2;i++){std::cout<<char(205);}
	std::cout<<char(190);
	
	int length=0;
	if (strlen(name)<xSize-4) {length=strlen(name);}
	else {length=xSize-4;}
	
	for (int i=0;i<length;i++)
	{
		setCur(xPos+i+2,yPos);
		setColor(15,8);
		std::cout<<name[i];
	}
	
	setColor(15,0);
	
}

void namedFrame2(char *name, int xPos, int yPos, unsigned xSize, unsigned ySize)
{
	
	
	setCur(xPos,yPos);std::cout<<char(213);
	for(unsigned i=0; i<xSize-2;i++){std::cout<<char(205);}
	std::cout<<char(184);

	for(unsigned y=yPos+1; y<yPos+ySize-1;y++)
	{
		setCur(xPos,y);std::cout<<char(179);
		for(unsigned n=0;n<xSize-2;n++){std::cout<<" ";}
		std::cout<<char(179);
	}

	setCur(xPos,yPos+ySize-1);std::cout<<char(212);
	for(unsigned i=0; i<xSize-2;i++){std::cout<<char(205);}
	std::cout<<char(190);
	
	int length=0;
	if (strlen(name)<xSize-4) {length=strlen(name);}
	else {length=xSize-4;}
	
	setCur(xPos+2,yPos);std::cout<<" ";
	for (int i=0;i<length;i++)
	{
		setCur(xPos+i+3,yPos);
		
		std::cout<<name[i];
	}
	std::cout<<" ";
	
	
}