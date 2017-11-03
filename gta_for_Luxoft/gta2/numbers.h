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

extern int roadXSize;
extern int roadYSize;

extern int screenSizeX;
extern int screenSizeY;

extern int ySpeedDivisor;
extern int xSpeedDivisor;

extern float xSpeedInhibitor;

extern float maxSpeedX;
extern float maxSpeedY;

extern int xMaxPosition;
extern int xMinPosition;

extern int carXSize;
extern int carYSize;

extern int controlSensitivity;


#endif NUMBERS_H