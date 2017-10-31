#pragma once
#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>
#include "road.h"

using namespace std;


class MyCar
{
public:
int xSize;
int ySize;
int roadSizeX;
int roadSizeY;
float yPosition;
MyCar(int roadXSize,int roadYSize,int **road):
		xSize(4),
		ySize(5),
		sensitivity_(4),
		xPosition_(20),
		yPosition(0),
		dSpeed_(0),
		dAlfa_(0)
{
	roadSizeX=roadXSize;
	roadSizeY=roadYSize;
	int **roadArray=road;
}


void message(string mes)
{
SetColor(15,4);
int startX=int((68-mes.size())/2);
setcur(startX,10);for(int a=0;a<mes.size()+2;a++){cout<<"=";}
setcur(startX,11);cout<<" "<<mes<<" ";
setcur(startX,12);for(int a=0;a<mes.size()+2;a++){cout<<"=";}
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
	setcur(6,0);cout <<"Speed - " ;cout <<dSpeed_*10<<" km/h  ";
	setcur(25,0);cout <<"Time - "  ;cout <<getTime()<<"   ";
	setcur(45,0);cout <<"Distance - ";cout <<int(yPosition)<<" m.   ";
}
void control()
{
	int key=0;
	if(_kbhit())
	{
		key=_getch();
		
		if (key == 72 && dSpeed_<15){dSpeed_+=1;}
  		if (key == 80 && dSpeed_>0){dSpeed_-=1;}
		if (key == 75 && dAlfa_>-5 && dSpeed_!=0){dAlfa_=-sensitivity_;}
		if (key == 77 && dAlfa_<5  && dSpeed_!=0){dAlfa_= sensitivity_;}
		if (key == 27){exit(0);}
		if (key == 13){pause();}
	} 
		else if (dAlfa_>0){dAlfa_-=0.5;}
		else if (dAlfa_<0){dAlfa_+=0.5;}

	yPosition=yPosition+(dSpeed_/10); 
	if (xPosition_+(dAlfa_/5)>=6 && xPosition_+(dAlfa_/5)<=32){xPosition_=xPosition_+(dAlfa_/5);} 
	
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
	int screenSizeX=40;
	int screenSizeY=25;
	int dy=int(yPosition);
	for(int y=screenSizeY;y>=0;y--)
	{
		for(int x=0;x<=screenSizeX-1;x++)
		{
			if (roadArray[x][y+dy]==11){pixel=219;}//border
			if (roadArray[x][y+dy]==10){pixel=176;}//marking
			if (roadArray[x][y+dy]==13){pixel=177;}//pit
			if (roadArray[x][y+dy]==0){pixel=32;}
		
			screen_[x][y]=pixel;
		}
	}
	
carToScreen();
infoPanel();
//............................print
setcur(0,2);
for(int y=screenSizeY;y>=0;y--)
	{
	cout <<"\t      ";
	for(int x=0;x<=screenSizeX;x++)
		{
		if(screen_[x][y]==219){SetColor(15,15);}
		if(screen_[x][y]==176){SetColor(15,8);}
		if(screen_[x][y]==177){SetColor(15,7);}
		cout << char(screen_[x][y]);	
		if(screen_[x][y]!=32){SetColor(15,0);}
		}
	cout <<"\n";
	}

}
bool isCrash(int **roadArray)
{
bool crash=false;
for (int y=0;y<ySize;y++)
	{
	for (int x=0;x<xSize;x++)
		{
		if(roadArray[int(xPosition_)+x][int(yPosition)+y]==13){crash=1;}
		}
	}
return crash;
}
bool isFinish()
{
	int finishPosition=30;
	if(yPosition>(roadSizeY-finishPosition)){return 1;}else{return 0;}
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
	dSpeed_=0;
	dAlfa_=0;
	resetTime();
}


private:
int sensitivity_;
int oldTime_;
int newTime_;
int pauseTime_;
float xPosition_;
float dSpeed_;
float dAlfa_;
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

