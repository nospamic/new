//#ifndef MYCAR_H
//#define MYCAR_H
#pragma once

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>

class MyCar
{
public:
float yPosition;
MyCar();

void message(std::string mes);

void resetTime();

void infoPanel();

void control();

void carToScreen();

void printScreen(int yPosition, int *roadArray);

bool isCrash(int *roadArray);

bool isFinish();

void pause();

void restart();


private:

int oldTime_;
int newTime_;
int pauseTime_;
float xPosition_;
float ySpeed_;
float xSpeed;
int screen_ [41][31];
SYSTEMTIME st;

int TimeToNumber();

std::string NumberToTime(float number);

std::string getTime();

void setcur(int x, int y);

void SetColor(int text, int background);

};


//#endif MYCAR_H