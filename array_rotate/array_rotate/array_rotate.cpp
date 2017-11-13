#include <iostream>
#include <conio.h>
#include <vector>
#include "rotate.h"


int sizeX=20;
int sizeY=23;
int centerX=0;
int centerY=0;
int *ary=new int[sizeX*sizeY];

void zeroFilling()
{
	for(int y=0; y<sizeY; y++)
	{
		for (int x=0; x<sizeX; x++){ary[x+sizeX*y]=0;}
	}

}



void filling()
{
	for (int x=0; x<sizeX; x++){ary[x+sizeX*0]=1;}
}


int main() 	
{
	Rotate rotate;

	zeroFilling();
	filling();

	int *temp = rotate.rotateArray(sizeX, sizeY, centerX, centerY, ary, 30);
	rotate.print(sizeX, sizeY, temp);

	system ("pause");
	return (0);

}





