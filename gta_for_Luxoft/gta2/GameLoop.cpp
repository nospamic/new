
#include "GameLoop.h"

#include "MyCar.h"
#include "Road.h"

Road road;
int *roadArray=road.getRoadArray();

MyCar myCar;


void GameLoop::level(int scale)
{
while(true)
{
	myCar.restart();
	myCar.printScreen(myCar.yPosition, roadArray);
	myCar.pause();
	while(true)
	{
		myCar.control();
		Sleep (10);
		myCar.printScreen(myCar.yPosition, roadArray);
		if (myCar.isCrash(roadArray))
		{
			myCar.message("Game over!");
			break;
		}
		if (myCar.isFinish())
		{
			myCar.message("Welcome to Luxoft!");
			break;
		}
	}
}
}