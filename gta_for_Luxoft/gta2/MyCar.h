#pragma once
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "numbers.h"

using namespace std;


class MyCar
{
public:
float yPosition;
MyCar(){}
void message(string mes)
{
SetColor(15,4);
int startX=int((68-mes.size())/2);
setcur(startX,10);for(int a=0;a<mes.size()+2;a++){std::cout<<"=";}
setcur(startX,11);std::cout<<" "<<mes<<" ";
setcur(startX,12);for(int a=0;a<mes.size()+2;a++){std::cout<<"=";}
Sleep (200);
pause();
SetColor(15,0);
}
void resetTime()
{
oldTime_=TimeToNumber();
}
void infoPanel()
{
	setcur(6,0);std::cout <<"Speed - " ;std::cout <<ySpeed_*10<<" km/h  ";
	setcur(25,0);std::cout <<"Time - "  ;std::cout <<getTime()<<"   ";
	setcur(45,0);std::cout <<"Distance - ";std::cout <<int(yPosition)<<" m.   ";
}
void control()
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
	
	if (xPosition_+(xSpeed/xSpeedDivisor)>=xMinPosition && xPosition_+(xSpeed/xSpeedDivisor)<=xMaxPosition)
	{xPosition_=xPosition_+(xSpeed/xSpeedDivisor);} 
	
}
void carToScreen()
{
	screen_ [int(xPosition_)][4]=213;screen_ [int(xPosition_)+1][4]=223; screen_ [int(xPosition_)+2][4]=223;screen_ [int(xPosition_)+3][4]=184;
	screen_ [int(xPosition_)][3]=179;screen_ [int(xPosition_)+1][3]= 32; screen_ [int(xPosition_)+2][3]= 32;screen_ [int(xPosition_)+3][3]=179;
	screen_ [int(xPosition_)][2]=186;screen_ [int(xPosition_)+1][2]=219; screen_ [int(xPosition_)+2][2]=219;screen_ [int(xPosition_)+3][2]=186;
	screen_ [int(xPosition_)][1]=186;screen_ [int(xPosition_)+1][1]=219; screen_ [int(xPosition_)+2][1]=219;screen_ [int(xPosition_)+3][1]=186;
	screen_ [int(xPosition_)][0]=212;screen_ [int(xPosition_)+1][0]=205; screen_ [int(xPosition_)+2][0]=205;screen_ [int(xPosition_)+3][0]=190;
}
void printScreen(int yPosition, int **roadArray)
{
	int pixel;
	int yIntPosition=int(yPosition);
	for(int y=screenSizeY;y>=0;y--)
	{
		for(int x=0;x<=screenSizeX-1;x++)
		{
			if (roadArray[x][y+yIntPosition]==Point_BORDER){pixel=Char_BORDER;}
			if (roadArray[x][y+yIntPosition]==Point_MARKING){pixel=Char_MARKING;}
			if (roadArray[x][y+yIntPosition]==Point_PIT){pixel=Char_PIT;}
			if (roadArray[x][y+yIntPosition]==Point_EMPTY){pixel=Char_EMPTY;}
		
			screen_[x][y]=pixel;
		}
	}
	
carToScreen();
infoPanel();
//............................print
setcur(0,2);
for(int y=screenSizeY;y>=0;y--)
	{
	std::cout <<"\t      ";
	for(int x=0;x<screenSizeX;x++)
		{
		if(screen_[x][y]==Char_BORDER){SetColor(Color_White,Color_White);}
		if(screen_[x][y]==Char_MARKING){SetColor(Color_White,Color_DarkGray);}
		if(screen_[x][y]==Char_PIT){SetColor(Color_White,Color_LightGray);}
		std::cout << char(screen_[x][y]);	
		if(screen_[x][y]!=Char_EMPTY){SetColor(Color_White,Color_Black);}
		}
	std::cout <<"\n";
	}

}
bool isCrash(int **roadArray)
{
bool crash=false;
for (int y=0;y<carYSize;y++)
	{
	for (int x=0;x<carXSize;x++)
		{
		if(roadArray[int(xPosition_)+x][int(yPosition)+y]==Point_PIT){crash=true;}
		}
	}
return crash;
}
bool isFinish()
{
	int finishPosition=30;
	if(yPosition>(roadYSize-finishPosition)){return 1;}else{return 0;}
}
void pause()
{
	pauseTime_=TimeToNumber();
	Sleep (200);
	if(kbhit()){while(kbhit()){int a=getch();}}//kill bufer!!
	while(!getch()){}
	oldTime_+=(TimeToNumber()-pauseTime_);
}
void restart()
{
	yPosition=0;xPosition_=20;
	ySpeed_=0;
	xSpeed=0;
	resetTime();
}


private:

int oldTime_;
int newTime_;
int pauseTime_;
float xPosition_;
float ySpeed_;
float xSpeed;
int screen_ [41][31];
SYSTEMTIME st;

int TimeToNumber()
{
int Min;int Sec;int Mil;
GetLocalTime(&st);
Min=st.wMinute;Sec=st.wSecond;Mil=st.wMilliseconds;
return Min*60000+Sec*1000+Mil;
}
string NumberToTime(float number)
{
float Min;float Sec;float Mil;
Min=int(number/60000);
Sec=int((number-Min*60000)/1000);
Mil=int((number-Min*60000-Sec*1000)/10);

ostringstream sMin;sMin << Min;
ostringstream sSec;sSec << Sec;
ostringstream sMil;sMil << Mil;

string fulTime=sMin.str()+":"+sSec.str()+":"+sMil.str();
return fulTime;

}
string getTime()
{
newTime_=TimeToNumber();
string fulTime=NumberToTime(float(newTime_-oldTime_));
return fulTime;
}
void setcur(int x, int y) 
{ 
COORD coord; 
coord.X = x; 
coord.Y = y; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
};
void SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

};


