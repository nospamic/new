#pragma once
#include <iostream>
#include <conio.h>
#include <vector>

class Rotate
{
private:

	int round(double a);
	
	double angle(int x, int y, int centerX, int centerY);
	
	double radius(double x, double y, int centerX, int centerY);

	int rotateX(double x, double y, int centerX, int centerY, double fi); 

	int rotateY(double x, double y, int centerX, int centerY, double fi);


public:
	
	int *rotateArray(int sizeX, int sizeY, int centerX, int centerY, int *arr, double alpha);

	void print(int sizeX, int sizeY, int *arr);

	
};
