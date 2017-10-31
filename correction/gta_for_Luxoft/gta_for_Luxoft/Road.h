#pragma once
#include "iostream"
#include <conio.h>
#include <ctime>

using namespace std;

class Road
{
public:
	int xSize;
	int ySize;
	Road(int XSize,int YSize)
	{
		xSize=XSize;
		ySize=YSize;
		
	}

	int **makeRoadArray(int xSize, int ySize)
	{
		int **road = new int *[xSize];
		for (int i = 0; i < xSize; i++) {road[i] = new int [ySize];}
		return road;
	}

	int **getRoadArray()
	{
		int **roadArray=makeRoadArray(xSize,ySize);

		for (int y=0;y<ySize;y++)
		{
			for (int x=0;x<xSize;x++){roadArray[x][y]=0;}
		}

		int lineLength=6;
		int n=0;
		for (int y=0;y<ySize;y++)
		{
			roadArray[4][y]=10;roadArray[5][y]=11;roadArray[xSize-5][y]=11;roadArray[xSize-4][y]=10;
			if (n<lineLength) {roadArray[xSize/2][y]=10;}
			if (n==lineLength*2){n=0;}
			n++;
		}

		chessMarking(0,roadArray);
		chessMarking(ySize-30,roadArray);
		addPit(roadArray);

		return roadArray;
	}


private:

	void chessMarking(int position,int **roadArray)
	{
		bool isSolid;
		int squareSize=2;
		int n=0;
		int markingSizeY=10;
		for(int y=0;y<markingSizeY;y++)
		{
			n=0;
			if ((y % 2)>0) {isSolid=true;} else {isSolid=false;}
			for(int x=6;x<=xSize-6;x++)
			{
				if(isSolid){roadArray [x][y+position]=10;}else {roadArray[x][y+position]=0;}
				n++;
				if (n>=squareSize){isSolid=!isSolid;n=0;}
			}
		}

	}

	void addPit(int **roadArray)
	{
		int pitStart=20;
		int pitEnd=40;
		srand(time(0));
		for (int y=pitStart;y<(ySize-pitEnd);y++)
		{
			for(int x=7;x<xSize-9;x++)
			{
				int randomNumber=int(rand() % 100);
				if (randomNumber==1)
				{
					roadArray[x][y]=13;roadArray[x+1][y]=13;
					roadArray[x][y+1]=13;roadArray[x+1][y+1]=13;
					y+=5;
				}
			}
	
		}

	}



};
