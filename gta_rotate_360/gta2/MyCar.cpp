#include "MyCar.h"


MyCar::MyCar()
{
	yPosition=carYSize;
	xPosition=20.0;
	
	controlSensitivity = 4;
	maxSpeedX = 5.0;
	maxSpeedY = 15.0;
	ySpeedDivisor = 10;
	xSpeedDivisor = 5;
	xSpeedInhibitor = 0.5;
	course=1;

	alfa=0.0;
	deltaAlfa=0.0;
}


void MyCar::getKeyVector()
{
	if(kbhit())
	{
		while(kbhit()){keys.push_back(getch());}
	}
}


void MyCar::control()
{
	getKeyVector();
	
	for(int n=0;n<keys.size();n++)
	{
		if (keys[n]==KEY_UP){yMove=1;}
		if (keys[n]==KEY_DOWN){yMove=-1;}
		if (keys[n]==KEY_LEFT){xMove=-1;}
		if (keys[n]==KEY_RIGHT){xMove=1;}
	}
	if (keys.size()==0)
	{
		xMove=0;
		yMove=0;
	}
	keys.clear();
}


void MyCar::move(int scale)
{
		control();
		
		//alfa += deltaAlfa;
		deltaX = sin(alfa);
		deltaY = cos(alfa);

		xPosition += ySpeed * deltaX * 0.5;
		yPosition += ySpeed * deltaY * 0.5;
		
		if (yMove == 1 && ySpeed<maxSpeedY){ySpeed+=1;}
  		if (yMove == -1 && ySpeed>0){ySpeed-=1;}
		
		if (xMove == -1 ){alfa-=0.1;}
		if (xMove == 1 ){alfa+=0.1;}

		/*if (yMove == 1 && ySpeed<maxSpeedY){ySpeed+=1;}
  		if (yMove == -1 && ySpeed>0){ySpeed-=1;}
		if (xMove == -1 && xSpeed>-maxSpeedX && ySpeed!=0){xSpeed=-controlSensitivity;}
		if (xMove == 1 && xSpeed<maxSpeedX  && ySpeed!=0){xSpeed= controlSensitivity;}
	 
		if (xSpeed>0 && xMove==0){xSpeed-=xSpeedInhibitor;}
		if (xSpeed<0 && xMove==0){xSpeed+=xSpeedInhibitor;}

	yPosition=yPosition+(ySpeed/ySpeedDivisor); */
	
	/*if (xPosition+(xSpeed/xSpeedDivisor)>=xMinPosition && xPosition+(xSpeed/xSpeedDivisor)<=xMaxPosition)
		{xPosition=xPosition+(xSpeed/xSpeedDivisor);} */
	
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
				if(roadArray[(int(xPosition)+x)+roadXSize*(int(yPosition)+y+carYSize)]==Point_PIT){crash=true;}
			}
		}
	return crash;
}


bool MyCar::isFinish()
{
	if(int(yPosition)>=(roadYSize-screenSizeY-carYSize-1))
		{return 1;} else {return 0;}
}


void MyCar::restart(int scale)
{
	int minYSpeed=(scale-1)*5;
	yPosition=carYSize;
	xPosition=20.0;
	ySpeed=minYSpeed;
	xSpeed=0.0;
	keys.clear();
	if(kbhit()){while(kbhit()){int a=getch();}}//kill bufer!!
}



