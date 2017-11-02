

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "MyCar.h"
#include "Road.h"


//#include "numbers.h"

//using namespace std;



int main()
{
setlocale (LC_ALL,"Russian");
system("mode con lines=29 cols=70");
SetConsoleCP(1251);
SetConsoleOutputCP(1251);


Road road;

int *roadArray=road.getRoadArray();


MyCar myCar;

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

return 0;
}

