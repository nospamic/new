#include "numbers.h"
#include "Road.h"
#include "iostream"
#include <conio.h>
#include <ctime>




	void Road::chessMarking(int position,int *roadArray)
	{
		bool isSolid;
		int squareSize=2;
		int n=0;
		int markingSizeY=10;
		for(int y=0;y<markingSizeY;y++)
		{
			n=0;
			if ((y % 2)>0) {isSolid=true;} else {isSolid=false;}
			for(int x=6;x<=roadXSize-6;x++)
			{
				if(isSolid){roadArray [x*roadXSize+(y+position)]=10;}else {roadArray[x*roadXSize+(y+position)]=0;}
				n++;
				if (n>=squareSize){isSolid=!isSolid;n=0;}
			}
		}

	}

	

	int * Road::getRoadArray()
	{
		
		int *roadArray=new int[roadXSize*roadYSize];
		

		for (int y=0;y<roadYSize;y++)
		{
			for (int x=0;x<roadXSize;x++){roadArray[x*roadXSize+y]=0;}
		}

		int lineLength=6;
		int n=0;
		for (int y=0;y<roadYSize;y++)
		{
			roadArray[4*roadXSize+y]=10;roadArray[5*roadXSize+y]=11;roadArray[(roadXSize-5)*roadXSize+y]=11;roadArray[(roadXSize-4)*roadXSize+y]=10;
			if (n<lineLength) {roadArray[(roadXSize/2)*roadXSize+y]=10;}
			if (n==lineLength*2){n=0;}
			n++;
		}

		chessMarking(0,roadArray);
		chessMarking(roadYSize-30,roadArray);
		addPit(roadArray);

		return roadArray;
	}



	

	void Road::addPit(int *roadArray)
	{
		int pitStart=20;
		int pitEnd=40;
		srand(time(0));
		for (int y=pitStart;y<(roadYSize-pitEnd);y++)
		{
			for(int x=7;x<roadXSize-9;x++)
			{
				int randomNumber=int(rand() % 100);
				if (randomNumber==1)
				{
					roadArray[x*roadXSize+y]=13;roadArray[(x+1)*roadXSize+y]=13;
					roadArray[x*roadXSize+(y+1)]=13;roadArray[(x+1)*roadXSize+(y+1)]=13;
					y+=5;
				}
			}
	
		}

	}

