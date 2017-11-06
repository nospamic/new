#pragma once
#include "numbers.h"
#include <string>
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <sstream>

class Show
{
	private:
		int oldTime_;
		int newTime_;
		int pauseTime_;
		int screen_ [41][31];
		SYSTEMTIME st;

		int TimeToNumber();

		std::string NumberToTime(float number);

		std::string getTime();
	
		void setcur(int x, int y);

		void SetColor(int text, int background);

		void carToScreen(int *carArray,int carXPosition);

	public:

		void pause();
	
		void printScreen(int xPosition, int yPosition, int ySpeed,  int *roadArray, int *carArray);

		void message(std::string mes, int scale);

		void infoPanel(int ySpeed, int yPosition);

		void resetTime();
};

