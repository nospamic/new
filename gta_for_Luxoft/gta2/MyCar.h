#ifndef MYCAR_H
#define MYCAR_H
#pragma once

#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "numbers.h"


class MyCar
{
public:
float xPosition;
float yPosition;
MyCar();

void resetTime();

void infoPanel();

void control();

bool isCrash(int *roadArray);

bool isFinish();

void pause();

void restart();

int *getCarArray();

int getXPosition();

int getYPosition();

private:

int oldTime_;
int newTime_;
int pauseTime_;
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


#endif MYCAR_H