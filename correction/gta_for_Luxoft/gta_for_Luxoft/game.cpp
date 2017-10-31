#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "MyCar.h"
#include "Road.h"

using namespace std;



enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, 
				LightCyan, LightRed, LightMagenta, Yellow, White };





int main()
{
setlocale (LC_ALL,"Russian");
system("mode con lines=29 cols=70");
SetConsoleCP(1251);
SetConsoleOutputCP(1251);

int roadXSize=40;
int roadYSize=200;

Road road(roadXSize,roadYSize);
int **roadArray=road.getRoadArray();

MyCar myCar(roadXSize,roadYSize,roadArray);

while(true)
{
	myCar.restart();
	myCar.printScreen(myCar.yPosition,roadArray);
	myCar.pause();
	while(true)
	{
		myCar.control();
		Sleep (10);
		myCar.printScreen(myCar.yPosition,roadArray);
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

