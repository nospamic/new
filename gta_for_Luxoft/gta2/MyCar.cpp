
#include "MyCar.h"





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
	for (int y=0;y<ySize;y++)
		{
		for (int x=0;x<xSize;x++)
			{
			if(roadArray[(int(xPosition)+x)+roadXSize*(int(yPosition)+y)]==Point_PIT){crash=true;}
			}
		}
	return crash;
}


bool MyCar::isFinish()
{
	
	if(int(yPosition)>=(roadYSize-screenSizeY-1))
		{return 1;} else {return 0;}
}


void MyCar::restart(int scale)
{
	int minYSpeed=(scale-1)*5;
	yPosition=0;xPosition=20;
	ySpeed=minYSpeed;
	xSpeed=0;
}



