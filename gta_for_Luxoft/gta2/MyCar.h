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
float ySpeed;

MyCar();

void control(int scale);

bool isCrash(int *roadArray);

bool isFinish();

void pause();

void restart(int scale);

int *getCarArray();

int getXPosition();

int getYPosition();

private:

int oldTime_;
int newTime_;
int pauseTime_;
float xSpeed;
int screen_ [41][31];
SYSTEMTIME st;

};


#endif MYCAR_H