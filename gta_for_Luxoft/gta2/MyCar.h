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
float xSpeed;
float ySpeed;



void control(int scale);

bool isCrash(int *roadArray);

bool isFinish();

void restart(int scale);

int getXPosition();

int getYPosition();

private:

};


#endif MYCAR_H