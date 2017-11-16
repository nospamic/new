#pragma once
#include <iostream>
#include <conio.h>
#include <vector>

class Rotate
{
private:

	int round(float a);
	
	float angle(int x, int y, int centerX, int centerY);
	
	float radius(float x, float y, int centerX, int centerY);

	int rotateX(float x, float y, int centerX, int centerY, float fi); 

	int rotateY(float x, float y, int centerX, int centerY, float fi);


public:
	
	int *rotateArray(int sizeX, int sizeY, int centerX, int centerY, int *arr, float alpha);

	void print(int sizeX, int sizeY, int *arr);

	
};
