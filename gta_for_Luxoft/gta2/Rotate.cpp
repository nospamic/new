#include "Rotate.h"




const float PI=3.1415;

int Rotate::round(float a)
{
	if(a>=0)
	{
		if (a-int(a)>0.5){a=int(a+1);}
		else
			{a=int(a);}
	}
	if(a<0)
	{
		if (a-int(a)<-0.5){a=int(a-1);}
		else
			{a=int(a);}}
	return int(a);
}


void Rotate::print(int sizeX, int sizeY, int *arr)
{
	for(int y=0; y<sizeY; y++)
	{
		for (int x=0; x<sizeX; x++)
		{
			if (arr[x+sizeX*y]==0){std::cout << ".";} else {std::cout << arr[x+sizeX*y];}
		}
		std::cout << "\n";	
	}
}



float Rotate::angle(int x, int y, int centerX, int centerY) 
{
	
	float dx=x-centerX;float dy=y-centerY;
	float alpha = ((atan(dx/dy))/PI*180);
	if (dx<0&&dy<0){alpha=360-alpha;}
	if (dx<0&&dy>=0){alpha=180-alpha;}
	if (dx>=0&&dy>0){alpha=180-alpha;}
	if (dx>0&&dy<0){alpha=0-alpha;}
	if(dy==0&&dx>0){alpha=90;}
	if(dy==0&&dx<0){alpha=270;}
	if(dy==0&&dx==0){alpha=0;}
	return alpha;
}


float Rotate::radius(float x, float y, int centerX, int centerY) 
{
	float dx=abs(x-centerX); 
	float dy=abs(y-centerY);
	float r=float(sqrt(pow(dx,2)+pow(dy,2)));
	return r;
}



int Rotate::rotateX(float x, float y, int centerX, int centerY, float fi) 
{
	float alpha;
	float r=radius(x, y, centerX, centerY);
	float dx=x-centerX;
	float dy=y-centerY;
	alpha = angle(x, y, centerX, centerY);
	x=((cos((alpha+fi-90) * PI / 180))*r)+centerX;
	x=round(x);
	return x;
}



int Rotate::rotateY(float x, float y, int centerX, int centerY, float fi) 
{
	float r=radius(x, y, centerX, centerY);
	float dx=x-centerX; 
	float dy=y-centerY;
	float alpha = angle(x, y, centerX, centerY);
	y=((sin((alpha+fi-90) * PI / 180))*r)+centerY;
	y=round(y);
	return y;
}


int *Rotate::rotateArray(int sizeX, int sizeY, int centerX, int centerY, int *arr, float alpha)
{
	std::vector <int> temp;
	
	for(int y=0; y<sizeY; y++)
	{
		for (int x=0; x<sizeX; x++){temp.push_back(0);}
	}
	
	for(int y=0;y<sizeY;y++)
	{
		for(int x=0;x<sizeX;x++)
		{
			int x1=rotateX(float(x),float(y), centerX, centerY, alpha);
			int y1=rotateY(float(x),float(y), centerX, centerY, alpha);
			if (x1<sizeX && y1<sizeY && x1>=0 && y1>=0){temp[x1+sizeX*y1]=arr[x+sizeX*y];}
		}
	}

	for(int y=0; y<sizeY; y++)
	{
		for (int x=0; x<sizeX; x++){arr[x+sizeX*y]=temp[x+sizeX*y];}
	}

	return arr;

}