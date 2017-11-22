
#include "GameLoop.h"



void GameLoop::control()
{
	
	unsigned key1;
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
	int *roadArray=road.getRoadArray();
	
	AIcar car1(30,10);
	AIcar car2(14,90);
	AIcar car3(30,40);

	bool isDone=false;
	while(!isDone)
	{
		myCar.restart(scale);
		show.resetTime();
		
		car1.reset();
		car2.reset();
		car3.reset();
		show.clearAICarVector();
		
		show.setAICar(car1.xPosition,car1.yPosition, car1.course);
		car1.carShadow(roadArray);
		show.setAICar(car2.xPosition,car2.yPosition, car2.course);
		car2.carShadow(roadArray);
		show.setAICar(car3.xPosition,car3.yPosition, car3.course);
		car3.carShadow(roadArray);

		show.printScreen(myCar.xPosition, myCar.yPosition, myCar.xSpeed, myCar.ySpeed, roadArray);
		show.message("Welcome to level ",scale);
		while(true)
		{
			myCar.move(scale);
			Sleep (10);
			
			show.clearAICarVector();
			
			car1.carShadowRemove(roadArray);
			show.setAICar(car1.xMove(roadArray),car1.yMove(roadArray), car1.course);
			car1.carShadow(roadArray);
			
			car2.carShadowRemove(roadArray);
			show.setAICar(car2.xMove(roadArray),car2.yMove(roadArray), car2.course);
			car2.carShadow(roadArray);
			
			car3.carShadowRemove(roadArray);
			show.setAICar(car3.xMove(roadArray),car3.yMove(roadArray), car3.course);
			car3.carShadow(roadArray);

			show.printScreen(myCar.xPosition,myCar.yPosition, myCar.xSpeed, myCar.ySpeed, roadArray);
			if (myCar.isCrash(roadArray))
			{
				show.message("Game over!",0); 
				roadArray=road.getRoadArray();
				break;
			}
			
			if (myCar.isFinish())
			{
				show.message("Level completed.",0);
				myCar.restart(scale);
				isDone=true;
				roadArray=road.getRoadArray();
				
				break;
			}
			control();
		}
	}
	if (scale==2 && isDone){show.message("--== Welcome to Luxoft ==--",0);}
}
