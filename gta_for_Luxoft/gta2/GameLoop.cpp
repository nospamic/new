#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>

#include "GameLoop.h"
#include "MyCar.h"
#include "Road.h"
#include "Show.h"
#include "AIcar.h"

Road road;
int *roadArray=road.getRoadArray();
MyCar myCar;
int *carArray=myCar.getCarArray();

AIcar car1(10,5);
int *car1Array=car1.getCarArray();
AIcar car2(14,160);
int *car2Array=car2.getCarArray();
AIcar car3(30,40);
int *car3Array=car3.getCarArray();

Show show;


void GameLoop::control()
{
	
	int key1;
	if(_kbhit())
	{
		key1=_getch();
		if (key1 == KEY_ESCAPE)
			{exit(0);}
		if (key1 == KEY_ENTER)
			{show.pause();}
	}
}


void GameLoop::level(int scale)
{
	bool isDone=false;
	while(!isDone)
	{
		myCar.restart(scale);
		show.resetTime();
		
		car1.reset();
		car2.reset();
		show.clearAICarVector();
		show.setAICar(car1.xPosition,car1.yPosition, car1.getCarArray());
		show.setAICar(car2.xPosition,car2.yPosition, car2.getCarArray());
		show.setAICar(car3.xPosition,car3.yPosition, car3.getCarArray());

		show.printScreen(myCar.xPosition, myCar.yPosition, myCar.ySpeed, roadArray, carArray);
		show.message("Welcome to level ",scale);
		while(true)
		{
			myCar.control(scale);
			Sleep (10);
			
			
			show.clearAICarVector();
			show.setAICar(car1.xMove(roadArray),car1.yMove(), car1.getCarArray());
			show.setAICar(car2.xMove(roadArray),car2.yMove(), car2.getCarArray());
			show.setAICar(car3.xMove(roadArray),car3.yMove(), car3.getCarArray());
			
			show.printScreen(myCar.xPosition,myCar.yPosition, myCar.ySpeed, roadArray,carArray);
			if (myCar.isCrash(roadArray))
			{
				show.message("Game over!",0); break;
			}
			
			if (myCar.isFinish())
			{
				show.message("Level completed.",0);
				myCar.restart(scale);
				isDone=true;
				break;
			}
			control();
		}
	}
	if (scale==2 && isDone){show.message("--== Welcome to Luxoft ==--",0);}
}
