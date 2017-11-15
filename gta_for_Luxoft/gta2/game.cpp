

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "GameLoop.h"

int main()
{
	setlocale (LC_ALL,"Russian");
	system("mode con lines=29 cols=70");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	

	GameLoop play;
	play.level(1);
	play.level(2);


	return 0;
}

