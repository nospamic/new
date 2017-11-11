
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "MyCar.h"

int screenSizeX = 40;
int screenSizeY = 25;

int ySpeedDivisor = 10;
int xSpeedDivisor = 5;

float xSpeedInhibitor = 0.5;

float maxSpeedX = 5.0;
float maxSpeedY = 15.0;

int xMaxPosition = 32;
int xMinPosition = 6;

int carXSize = 4;
int carYSize = 5;

int controlSensitivity=4;



void MyCar::control(int scale)
{
	int key;
	if(_kbhit())
	{
		key=_getch();
		
		if (key == KEY_UP && ySpeed<maxSpeedY){ySpeed+=1;}
  		if (key == KEY_DOWN && ySpeed>0){ySpeed-=1;}
		if (key == KEY_LEFT && xSpeed>-maxSpeedX && ySpeed!=0){xSpeed=-controlSensitivity;}
		if (key == KEY_RIGHT && xSpeed<maxSpeedX  && ySpeed!=0){xSpeed= controlSensitivity;}
	} 
		else if (xSpeed>0){xSpeed-=xSpeedInhibitor;}
		else if (xSpeed<0){xSpeed+=xSpeedInhibitor;}

	yPosition=yPosition+(ySpeed/ySpeedDivisor); 
	
	if (xPosition+(xSpeed/xSpeedDivisor)>=xMinPosition && xPosition+(xSpeed/xSpeedDivisor)<=xMaxPosition)
	{xPosition=xPosition+(xSpeed/xSpeedDivisor);} 
	
}



int MyCar::getXPosition()
{
	return int(xPosition);
}

int MyCar::getYPosition()
{
	return int(yPosition);
}

bool MyCar::isCrash(int *roadArray)
{
	bool crash=false;
	for (int y=0;y<carYSize;y++)
		{
		for (int x=0;x<carXSize;x++)
			{
			if(roadArray[(int(xPosition)+x)+roadXSize*(int(yPosition)+y)]==Point_PIT){crash=true;}
			}
		}
	return crash;
}

bool MyCar::isFinish()
{
	int finishPosition=30;
	if(yPosition>(roadYSize-finishPosition))
		{return 1;} else {return 0;}
}


void MyCar::restart(int scale)
{
	int minYSpeed=(scale-1)*5;
	yPosition=0;xPosition=20;
	ySpeed=minYSpeed;
	xSpeed=0;
}



