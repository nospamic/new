#pragma once
#include <conio.h>
#include <windows.h>
#include "Box.h"
#include "Acces.h"
#include "Viewer.h"
#include "SelectDrive.h"
#include "numbers.h"


class Loop
{
Box boxLeft;
Box boxRight;


Acces acces;

public:
	Loop(void);
	~Loop(void);
	Box * boxActive;
	void go();

private:
	void control();
	void keyDown();
	void keyUp();
	void keyEnter();
	void keyTab();
	void keySpace();
};

