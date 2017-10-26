#include "iostream"
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <sstream>


using namespace std;


SYSTEMTIME st;
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, 
				LightCyan, LightRed, LightMagenta, Yellow, White };


class Road
{
//10-разметка 11-бордюр 13-яма
private:
void razmetka(int dy)
{
int kx=-1;int ky=1;
for(int y=0;y<10;y++)
	{
	for(int x=6;x<=34;x++)
		{
		roadArray[x][y+dy]=0;
		if (kx<=0 && ky>0){roadArray[x][y+dy]=10;} 
		if (kx>0 && ky<=0){roadArray[x][y+dy]=10;} 
		kx++;
		if(kx>2)kx=-1;
		}
	ky++;kx--;
	if(ky>1)ky=0;
	}

}
void pits()
{
srand(time(0));
for (int y=20;y<(yMax-40);y++)
	{
	for(int x=7;x<31;x++)
		{
		int rn=int(rand() % 100);
		if (rn==20)
			{
			roadArray[x][y]=13;roadArray[x+1][y]=13;
			roadArray[x][y+1]=13;roadArray[x+1][y+1]=13;
			y+=5;
			}
		}
	
	}

}
public:
int yMax;
int roadArray [40][200];


void makeRoad()
{
yMax=200;
for (int y=0;y<yMax;y++)
	{
	for (int x=0;x<40;x++)
		{roadArray[x][y]=0;}
	}

int n=0;
for (int y=0;y<yMax;y++)
	{
	roadArray[4][y]=10;roadArray[5][y]=11;roadArray[35][y]=11;roadArray[36][y]=10;
	if (n<6) {roadArray[20][y]=10;}
	if (n==12){n=0;}
	n++;
	}

razmetka(0);
razmetka(yMax-30);
pits();
}
}road;

class MyCar:Road
{
private:
int sensitivity;
int oldTime;
int newTime;
int pauseTime;
float xPosition;
float dSpeed;
float dAlfa;
int screen [41][31];
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
newTime=TimeToNumber();
string fulTime=NumberToTime(float(newTime-oldTime));
return fulTime;
}
void setcur(int x, int y) 
{ 
COORD coord; 
coord.X = x; 
coord.Y = y; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
};
public:
int xSize;
int ySize;
float yPosition;
MyCar():xSize(4),
		ySize(5),
		sensitivity(4),
		xPosition(20),
		yPosition(0),
		dSpeed(0),
		dAlfa(0)
{}

void SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
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
oldTime=TimeToNumber();
}
void infoPanel()
{

setcur(6,0);cout <<"Speed - " ;cout <<dSpeed*10<<" km/h  ";
setcur(25,0);cout <<"Time - "  ;cout <<getTime()<<"   ";
setcur(45,0);cout <<"Distance - ";cout <<int(yPosition)<<" m.   ";
//cout <<"    xPos = "<<xPos<<"   ";

}
void control()
{
int key=0;
if(_kbhit())
		{
		key=_getch();
		
		if (key == 72 && dSpeed<15){dSpeed+=1;}
  		if (key == 80 && dSpeed>0){dSpeed-=1;}
		if (key == 75 && dAlfa>-5 && dSpeed!=0){dAlfa=-sensitivity;}
		if (key == 77 && dAlfa<5  && dSpeed!=0){dAlfa= sensitivity;}
		if (key == 27){exit(0);}
		if (key == 13){pause();}
			
		} 
		
		else if (dAlfa>0){dAlfa-=0.5;}
		else if (dAlfa<0){dAlfa+=0.5;}

yPosition=yPosition+(dSpeed/10); //y-moove
if (xPosition+(dAlfa/5)>=6 && xPosition+(dAlfa/5)<=32){xPosition=xPosition+(dAlfa/5);} //x-moove	

		
}
void carToScreen()

{
//............................car to screen
screen [int(xPosition)][4]=213;screen [int(xPosition)+1][4]=223; screen [int(xPosition)+2][4]=223;screen [int(xPosition)+3][4]=184;
screen [int(xPosition)][3]=179;screen [int(xPosition)+1][3]= 32; screen [int(xPosition)+2][3]= 32;screen [int(xPosition)+3][3]=179;
screen [int(xPosition)][2]=186;screen [int(xPosition)+1][2]=219; screen [int(xPosition)+2][2]=219;screen [int(xPosition)+3][2]=186;
screen [int(xPosition)][1]=186;screen [int(xPosition)+1][1]=219; screen [int(xPosition)+2][1]=219;screen [int(xPosition)+3][1]=186;
screen [int(xPosition)][0]=212;screen [int(xPosition)+1][0]=205; screen [int(xPosition)+2][0]=205;screen [int(xPosition)+3][0]=190;
}
void printScreen(int yPosition)
{
//..........................road to screen
int pixelKod;
int dy=int(yPosition);
for(int y=25;y>=0;y--)
	{
	for(int x=0;x<=40;x++)
		{
		if (road.roadArray[x][y+dy]==11){pixelKod=219;}//обочина
		if (road.roadArray[x][y+dy]==10){pixelKod=176;}//разметка
		if (road.roadArray[x][y+dy]==13){pixelKod=177;}//яма
		if (road.roadArray[x][y+dy]==0){pixelKod=32;}//ничего
		
		screen[x][y]=pixelKod;
		}
	}
	
carToScreen();
infoPanel();
//............................print
setcur(0,2);
for(int y=25;y>=0;y--)
	{
	cout <<"\t      ";
	for(int x=0;x<=40;x++)
		{
		if(screen[x][y]==219){SetColor(15,15);}
		if(screen[x][y]==176){SetColor(15,8);}
		if(screen[x][y]==177){SetColor(15,7);}
		cout << char(screen[x][y]);	
		if(screen[x][y]!=32){SetColor(15,0);}
		}
	cout <<"\n";
	}

}
bool isCrash()
{
bool crash=0;
for (int y=0;y<ySize;y++)
	{
	for (int x=0;x<xSize;x++)
		{
		if(road.roadArray[int(xPosition)+x][int(yPosition)+y]==13){crash=1;}
		}
	}
return crash;
}
bool isFinish()
{
//cout <<road.yMax<<" "<< yPos;system("pause");
if(yPosition>(road.yMax-30)){return 1;}else{return 0;}

}
void pause()
{
pauseTime=TimeToNumber();
Sleep (200);
if(kbhit()){while(kbhit()){int a=getch();}}//kill bufer!!
while(!getch()){}
oldTime+=(TimeToNumber()-pauseTime);
}
void restart()
{
yPosition=0;xPosition=20;
dSpeed=0;
dAlfa=0;
resetTime();
}
}myCar;

int main()
{
setlocale (LC_ALL,"Russian");
system("mode con lines=29 cols=70");
SetConsoleCP(1251);
SetConsoleOutputCP(1251);

for(;;)
	{
	myCar.restart();
	road.makeRoad();
	myCar.printScreen(myCar.yPosition);
	myCar.pause();
	for(;;)
		{
		myCar.control();
		Sleep (10);//game speed
		myCar.printScreen(myCar.yPosition);
		if (myCar.isCrash())
			{
			myCar.message("Game over!");
			break;
			}
		if (myCar.isFinish())
			{
			myCar.message("Welcome to Luxoft!");
			break;
			}
		 }
	}

return 0;
}

