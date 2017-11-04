
#include "GameLoop.h"

#include "MyCar.h"
#include "Road.h"
#include "Show.h"

Road road;
int *roadArray=road.getRoadArray();
MyCar myCar;
int *carArray=myCar.getCarArray();
Show show;

void GameLoop::level(int scale)
{
while(true)
{
	myCar.restart();
	show.printScreen(myCar.xPosition,myCar.yPosition, roadArray,carArray);
	show.pause();
	while(true)
	{
		myCar.control();
		Sleep (10);
		show.printScreen(myCar.xPosition,myCar.yPosition, roadArray,carArray);
		if (myCar.isCrash(roadArray))
		{
			show.message("Game over!");
			break;
		}
		if (myCar.isFinish())
		{
			show.message("Welcome to Luxoft!");
			break;
		}
	}
}
}