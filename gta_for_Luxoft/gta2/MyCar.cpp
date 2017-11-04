
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "MyCar.h"

int screenSizeX = 40;
int screenSizeY = 25;

int ySpeedDivisor = 10;
int xSpeedDivisor = 5;

float xSpeedInhibitor = 0.5;

float maxSpeedX = 5.0;
float maxSpeedY = 15.0;

int xMaxPosition = 32;
int xMinPosition = 6;

int carXSize = 4;
int carYSize = 5;

int controlSensitivity=4;



MyCar::MyCar(void){}


void MyCar::resetTime()
{
	oldTime_=TimeToNumber();
}

void MyCar::infoPanel()
{
	setcur(6,0);std::cout <<"Speed - " ;std::cout <<ySpeed_*10<<" km/h  ";
	setcur(25,0);std::cout <<"Time - "  ;std::cout <<getTime()<<"   ";
	setcur(45,0);std::cout <<"Distance - ";std::cout <<int(yPosition)<<" m.   ";
}

void MyCar::control()
{
	int key;
	if(_kbhit())
	{
		key=_getch();
		
		if (key == KEY_UP && ySpeed_<maxSpeedY){ySpeed_+=1;}
  		if (key == KEY_DOWN && ySpeed_>0){ySpeed_-=1;}
		if (key == KEY_LEFT && xSpeed>-maxSpeedX && ySpeed_!=0){xSpeed=-controlSensitivity;}
		if (key == KEY_RIGHT && xSpeed<maxSpeedX  && ySpeed_!=0){xSpeed= controlSensitivity;}
		if (key == KEY_ESCAPE){exit(0);}
		if (key == KEY_ENTER){pause();}
	} 
		else if (xSpeed>0){xSpeed-=xSpeedInhibitor;}
		else if (xSpeed<0){xSpeed+=xSpeedInhibitor;}

	yPosition=yPosition+(ySpeed_/ySpeedDivisor); 
	
	if (xPosition+(xSpeed/xSpeedDivisor)>=xMinPosition && xPosition+(xSpeed/xSpeedDivisor)<=xMaxPosition)
	{xPosition=xPosition+(xSpeed/xSpeedDivisor);} 
	
}

int *MyCar::getCarArray()
{
	int*carArray=new int[carXSize*carYSize];
	carArray [0+carXSize*4]=213;carArray [1+carXSize*4]=223; carArray [2+carXSize*4]=223;carArray [3+carXSize*4]=184;
	carArray [0+carXSize*3]=179;carArray [1+carXSize*3]= 32; carArray [2+carXSize*3]= 32;carArray [3+carXSize*3]=179;
	carArray [0+carXSize*2]=186;carArray [1+carXSize*2]=219; carArray [2+carXSize*2]=219;carArray [3+carXSize*2]=186;
	carArray [0+carXSize*1]=186;carArray [1+carXSize*1]=219; carArray [2+carXSize*1]=219;carArray [3+carXSize*1]=186;
	carArray [0+carXSize*0]=212;carArray [1+carXSize*0]=205; carArray [2+carXSize*0]=205;carArray [3+carXSize*0]=190;
return carArray;
}

int MyCar::getXPosition()
{
	return int(xPosition);
}

int MyCar::getYPosition()
{
	return int(yPosition);
}

bool MyCar::isCrash(int *roadArray)
{
	bool crash=false;
	for (int y=0;y<carYSize;y++)
		{
		for (int x=0;x<carXSize;x++)
			{
			if(roadArray[(int(xPosition)+x)+roadXSize*(int(yPosition)+y)]==Point_PIT){crash=true;}
			}
		}
	return crash;
}

bool MyCar::isFinish()
{
	int finishPosition=30;
	if(yPosition>(roadYSize-finishPosition)){return 1;}else{return 0;}
}

void MyCar::pause()
{
	pauseTime_=TimeToNumber();
	Sleep (200);
	if(kbhit()){while(kbhit()){int a=getch();}}//kill bufer!!
	while(!getch()){}
	oldTime_+=(TimeToNumber()-pauseTime_);
}

void MyCar::restart()
{
	yPosition=0;xPosition=20;
	ySpeed_=0;
	xSpeed=0;
	resetTime();
}

int MyCar::TimeToNumber()
{
	int Min;int Sec;int Mil;
	GetLocalTime(&st);
	Min=st.wMinute;Sec=st.wSecond;Mil=st.wMilliseconds;
	return Min*60000+Sec*1000+Mil;
}

std::string MyCar::NumberToTime(float number)
{
	float Min;float Sec;float Mil;
	Min=int(number/60000);
	Sec=int((number-Min*60000)/1000);
	Mil=int((number-Min*60000-Sec*1000)/10);

	std::ostringstream sMin;sMin << Min;
	std::ostringstream sSec;sSec << Sec;
	std::ostringstream sMil;sMil << Mil;

	std::string fulTime=sMin.str()+":"+sSec.str()+":"+sMil.str();
	return fulTime;
	}

std::string MyCar::getTime()
{
	newTime_=TimeToNumber();
	std::string fulTime=NumberToTime(float(newTime_-oldTime_));
	return fulTime;
}

void MyCar::setcur(int x, int y) 
{ 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
};

void MyCar::SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
