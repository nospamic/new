#ifndef NUMBERS_H
#define NUMBERS_H

//#pragma once

enum Color { Color_Black = 0, Color_Blue, Color_Green, Color_Cyan, Color_Red, Color_Magenta, Color_Brown, Color_LightGray, 
				Color_DarkGray, Color_LightBlue, Color_LightGreen, 
				Color_LightCyan, Color_LightRed, Color_LightMagenta, 
				Color_Yellow, Color_White };

enum key{KEY_UP=72, KEY_DOWN=80, KEY_LEFT=75, KEY_RIGHT=77, KEY_ENTER=13, KEY_ESCAPE=27};

enum Char{Char_BORDER=219, Char_MARKING=176, Char_PIT=177, Char_EMPTY=32};

enum Point{Point_PIT=13, Point_MARKING=10, Point_BORDER=11, Point_EMPTY=0};

int roadXSize = 40;
int roadYSize = 200;

int screenSizeX = 40;
int screenSizeY = 25;

int ySpeedDivisor = 10;
int xSpeedDivisor = 5;

float xSpeedInhibitor = 0.5;

float maxSpeedX = 5.0;
float maxSpeedY = 15.0;

int xMaxPosition = 32;
int xMinPosition = 6;

int carXSize = 4;
int carYSize = 5;

int controlSensitivity=4;


#endif NUMBERS_H