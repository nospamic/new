#include "AIcar.h"




AIcar::AIcar(int xStart, int yStart)
{
	xPosition=xStart;
	yPosition=yStart;
	xStartPosition=xStart;
	yStartPosition=yStart;

	if (yStartPosition<(roadYSize/2))
		{course=1; ySpeed=.5; finishPosition=roadYSize-ySize;}
	else
		{course=-1; ySpeed=-.5; finishPosition=ySize;}
}


void AIcar::carShadow(int *roadArray)
{
	roadSnapshot.clear();
	for(int y=0; y<ySize;y++)
		{
			for(int x=0; x<xSize; x++)
			{
				int xMarking=x+xPosition;
				int yMarking=y+(yPosition);
				roadSnapshot.push_back(roadArray[xMarking+roadXSize*yMarking]);
				roadArray[xMarking+roadXSize*yMarking] = Point_PIT;
			}
		}
}


void AIcar::carShadowRemove(int *roadArray)
{
	for(int y=0; y<ySize;y++)
		{
			for(int x=0; x<xSize; x++)
			{
				int xMarking=x+xPosition;
				int yMarking=y+(yPosition);
				roadArray[xMarking+roadXSize*yMarking] = roadSnapshot[x+carXSize*y];
			}
		}
}


void AIcar::reset()
{
	xPosition=xStartPosition;
	yPosition=yStartPosition;
}


int AIcar::xMove(int *roadArray)
{
	xSpeed=0;
	
	if(isPit(roadArray) && course==1) {xSpeed=-1;}
	if(isPit(roadArray) && course==-1) {xSpeed=1;}
	

	if (course==-1 && !isPit(roadArray) && xPosition>xMinPosition+xSize/2 && !isPitLeft(roadArray))
		{xSpeed=-1;}
	if (course==1 && !isPit(roadArray) && xPosition<xMaxPosition-xSize && !isPitRight(roadArray))
		{xSpeed=1;}
	//carShadowRemove(roadArray);
	
	if (xPosition+xSpeed>=xMinPosition && xPosition+xSpeed<=xMaxPosition)
		{xPosition+=xSpeed;}
	
	return xPosition;
}


bool AIcar::isPit(int *roadArray)
{
	bool isPit=false;
	viewDistance=10;
	if (course==1)
	{
		for(int y=ySize; y<viewDistance;y++)
		{
			for(int x=0; x<xSize; x++)
			{
				int xTesting=x+xPosition;
				int yTesting=y+(yPosition);
			
				if(roadArray[xTesting+roadXSize*yTesting]==Point_PIT) {isPit=true;}
			}
		}
	}else{
		for(int y=-1; y>(-viewDistance+ySize);y--)
			{
				for(int x=0; x<xSize; x++)
				{
					int xTesting=x+xPosition;
					int yTesting=y+(yPosition);
			
					if(roadArray[xTesting+roadXSize*yTesting]==Point_PIT) {isPit=true;}
						//else{roadArray[xTesting+roadXSize*yTesting]=Point_MARKING;}
				}
			}
	
	
	}
return isPit;
}

bool AIcar::isPitLeft(int *roadArray)
{
	bool isPit=false;
	viewDistance=ySize;
	for(int y=0; y<viewDistance;y++)
	{
		
			int xTesting=xPosition-1;
			int yTesting=y+(yPosition);
			
			if(roadArray[xTesting+roadXSize*yTesting]==Point_PIT) {isPit=true;}
			//else{roadArray[xTesting+roadXSize*yTesting]=Point_MARKING;}
	}
	return isPit;
}


bool AIcar::isPitRight(int *roadArray)
{
	bool isPit=false;
	viewDistance=ySize;
	for(int y=0; y<viewDistance;y++)
	{
			int xTesting=xPosition+xSize+1;
			int yTesting=y+(yPosition);
			
			if(roadArray[xTesting+roadXSize*yTesting]==Point_PIT) {isPit=true;}
			//else{roadArray[xTesting+roadXSize*yTesting]=Point_MARKING;}
	}
return isPit;
}

int AIcar::yMove(int *roadArray)
{
	if(course==1 && yPosition+ySpeed>=finishPosition || course==-1 && yPosition+ySpeed<=finishPosition)
	{
		if (course==1){finishPosition=ySize;}
		else{finishPosition=roadYSize-ySize;}
		
		yPosition-=ySpeed;
		ySpeed=ySpeed*(-1);
		course=course*(-1);
	}
	else
	{
		yPosition+=ySpeed;
	}
	return yPosition;
}


bool AIcar::isCrash(int *screenArray)
{
return false;
}