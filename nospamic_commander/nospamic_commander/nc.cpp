#include <iostream>

#include <windows.h>
#include <vector>
#include <direct.h>
#include "Loop.h"





int main(int argc, char **argv)
{
	//glutInit(&argc, argv);
	setlocale (LC_ALL,"Russian");
	system("mode con lines=31 cols=80");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	Loop loop;
	loop.go();

	/*Acces acc;

	Box boxLeft(1);
	Box boxRight(2);
	boxLeft.showBox();
	acc.changeDir("..");
	boxRight.showBox();*/

	system("pause");
	return 0;
}