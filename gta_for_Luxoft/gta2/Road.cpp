
#include "Road.h"



Road::Road()
{
	markingSizeY=10;
	pitStart=30;
	pitEnd=40;
	lineLength=6;
}


Road::~Road()
{

}
	

void Road::borderLineMarking(int *roadArray)
{
	int n=0;
	int lineLengthBorder=lineLength/2;
	for (int y=0;y<roadYSize;y++)
		{
			if (n<lineLengthBorder) 
			{
				roadArray[4+roadXSize*y]=Point_MARKING;
				roadArray[3+roadXSize*y]=Point_MARKING;
				roadArray[2+roadXSize*y]=Point_MARKING;
				roadArray[1+roadXSize*y]=Point_MARKING;

				roadArray[(roadXSize-4)+roadXSize*y]=Point_MARKING;
				roadArray[(roadXSize-3)+roadXSize*y]=Point_MARKING;
				roadArray[(roadXSize-2)+roadXSize*y]=Point_MARKING;
				roadArray[(roadXSize-1)+roadXSize*y]=Point_MARKING;
			}
			if (n==lineLengthBorder){n=0;}
			n++;
		}

}


void Road::chessMarking(int position,int *roadArray)
{
		bool isSolid;
		int squareSize=2;
		int n=0;
		
		for(int y=0;y<markingSizeY;y++)
		{
			n=0;
			if ((y % 2)>0) {isSolid=true;} else {isSolid=false;}
			for(int x=6;x<=roadXSize-6;x++)
			{
				if(isSolid){roadArray [x+roadXSize*(y+position)]=10;}else {roadArray[x+roadXSize*(y+position)]=0;}
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
			for (int x=0;x<roadXSize;x++){roadArray[x+roadXSize*y]=0;}
		}

		
		int n=0;
		
		
		for (int y=0;y<roadYSize;y++)
		{
			
			roadArray[5+roadXSize*y]=Point_BORDER;
			roadArray[(roadXSize-5)+roadXSize*y]=Point_BORDER;
			
			if (n<lineLength) {roadArray[(roadXSize/2)+roadXSize*y]=Point_MARKING;}
			if (n==lineLength*2){n=0;}
			n++;
		}

		chessMarking(0,roadArray);
		chessMarking(roadYSize-screenSizeY,roadArray);
		borderLineMarking(roadArray);
		addPit(roadArray);

		

		return roadArray;
	}



	

void Road::addPit(int *roadArray)
{
		
		srand(time(0));
		for (int y=pitStart;y<(roadYSize-pitEnd);y++)
		{
			for(int x=7;x<roadXSize-9;x++)
			{
				int randomNumber=int(rand() % 100);
				if (randomNumber==1)
				{
					roadArray[x+roadXSize*y]=Point_PIT;roadArray[(x+1)+roadXSize*y]=Point_PIT;
					roadArray[x+roadXSize*(y+1)]=Point_PIT;roadArray[(x+1)+roadXSize*(y+1)]=Point_PIT;
					y+=5;
				}
			}
	
		}

}

