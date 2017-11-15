//#ifndef GAMELOOP_H
//#define GAMELOOP_H
#pragma once

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>

#include "MyCar.h"
#include "Road.h"
#include "Show.h"
#include "AIcar.h"

class GameLoop
{

	Road road;
	MyCar myCar;
	Show show;


public:
	void control();
	void level(int scale);
	
};

//#endif GAMELOOP_H