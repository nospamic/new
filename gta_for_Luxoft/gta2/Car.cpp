#include "car.h"

Car::Car()
{
	xSize=4;
	ySize=5;

	xSpeed=0;
	finishPosition=roadYSize-carYSize;

	xMaxPosition = 32;
	xMinPosition = 6;
}

Car::~Car()
{

}