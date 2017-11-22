#pragma once
#include "numbers.h"
#include <string>
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <sstream>
#include <vector>
#include "Rotate.h"

class Show
{
	Rotate rotate;

	private:
		int *expandedScreen;
		int screenExpand;
		int expScreenSizeX;
		int expScreenSizeY;
		
		int *carArray;

		int oldTime_;
		int newTime_;
		int pauseTime_;
		
		int volume_[41][31];
		SYSTEMTIME st;

		void expandedToScreen();

		void makeVolume();

		void printRotate180();

		void getCarArray(int course);

		int TimeToNumber();

		std::string NumberToTime(float number);

		std::string getTime();
	
		void setcur(int x, int y);

		void SetColor(int text, int background);

		void carToScreen(int carXPosition);

		void aiCarToScreen(int yPosition);

		bool isCarOnScreen(int aiX, int aiY, int yPosition);


		

	public:
		Show();
		~Show();

		int *screen;
		
		
		std::vector<int>aiXPosition;
		std::vector<int>aiYPosition;
		std::vector<int>aiCarCourse;

		void clearAICarVector();

		void setAICar(int xPosition, int yPosition, int course);

		void pause();
	
		void printScreen(int xPosition, int yPosition, float xSpeed, int ySpeed,  int *roadArray);

		void message(std::string mes, int scale);

		void infoPanel(int ySpeed, int yPosition);

		void resetTime();

		void resetScreen();
};

