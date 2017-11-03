

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
//#include "MyCar.h"
//#include "Road.h"
#include "GameLoop.h"

int main()
{
	setlocale (LC_ALL,"Russian");
	system("mode con lines=29 cols=70");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	

	GameLoop game;
	game.level(1);


	return 0;
}

