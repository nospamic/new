#pragma once
#include "iostream"
#include <conio.h>
#include <ctime>




class Road
{
public:
	int xSize;
	int ySize;
	Road(int XSize,int YSize);
	

	int **makeRoadArray(int xSize, int ySize);
	

	int **getRoadArray();
	

private:

	void chessMarking(int position,int **roadArray);
	

	void addPit(int **roadArray);
	



};
