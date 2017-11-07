#include "Show.h"


void Show::setAICar(int xPosition, int yPosition, int *carArray)
{
	aiXPosition.push_back(xPosition);
	aiYPosition.push_back(yPosition);
	aiCarArray.push_back(carArray);
}


void Show::infoPanel(int ySpeed, int yPosition)
{
	setcur(6,0);std::cout <<"Speed - " ;std::cout <<ySpeed*10<<" km/h  ";
	setcur(25,0);std::cout <<"Time - "  ;std::cout <<getTime()<<"   ";
	setcur(45,0);std::cout <<"Distance - ";std::cout <<int(yPosition)<<" m.   ";
}


void Show::printScreen(int xPosition, int yPosition, int ySpeed, int *roadArray, int *carArray)
{
	int pixel;

	int yIntPosition=int(yPosition);
	for(int y=screenSizeY;y>=0;y--)
	{
		for(int x=0;x<=screenSizeX-1;x++)
		{
			if (roadArray[x+roadXSize*(y+yIntPosition)]==Point_BORDER){pixel=Char_BORDER;}
			if (roadArray[x+roadXSize*(y+yIntPosition)]==Point_MARKING){pixel=Char_MARKING;}
			if (roadArray[x+roadXSize*(y+yIntPosition)]==Point_PIT){pixel=Char_PIT;}
			if (roadArray[x+roadXSize*(y+yIntPosition)]==Point_EMPTY){pixel=Char_EMPTY;}
		
			screen_[x][y]=pixel;
		}
	}
	
	carToScreen(carArray, xPosition);
	infoPanel(ySpeed, yPosition);
	//............................print & turn 180
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

void Show::carToScreen(int *carArray,int carXPosition)
{
	for (int y=0; y<carYSize;y++)
	{
		for (int x=0; x<carXSize;x++)
		{
		screen_[carXPosition+x][y]=carArray[x+carXSize*y];
		}
	}
}

void Show::pause()
{
	pauseTime_=TimeToNumber();
	Sleep (200);
	if(kbhit()){while(kbhit()){int a=getch();}}//kill bufer!!
	while(!getch()){}
	oldTime_+=(TimeToNumber()-pauseTime_);
}

void Show::message(std::string mes, int scale)
{
	SetColor(15,4);
	if (scale==0)
	{
		int startX=int((68-mes.size())/2);
		setcur(startX,10);for(int a=0;a<mes.size()+2;a++){std::cout<<"=";}
		setcur(startX,11);std::cout<<" "<<mes<<" ";
		setcur(startX,12);for(int a=0;a<mes.size()+2;a++){std::cout<<"=";}
	}
	else
	{
		int startX=int((68-mes.size())/2);
		setcur(startX,10);for(int a=0;a<mes.size()+3;a++){std::cout<<"=";}
		setcur(startX,11);std::cout<<" "<<mes<<scale<<" ";
		setcur(startX,12);for(int a=0;a<mes.size()+3;a++){std::cout<<"=";}
	}
	Sleep (200);
	pause();
	SetColor(15,0);
}

void Show::setcur(int x, int y) 
{ 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
};

void Show::SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Show::resetTime()
{
	oldTime_=TimeToNumber();
}

int Show::TimeToNumber()
{
	int Min;int Sec;int Mil;
	GetLocalTime(&st);
	Min=st.wMinute;Sec=st.wSecond;Mil=st.wMilliseconds;
	return Min*60000+Sec*1000+Mil;
}

std::string Show::NumberToTime(float number)
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

std::string Show::getTime()
{
	newTime_=TimeToNumber();
	std::string fulTime=NumberToTime(float(newTime_-oldTime_));
	return fulTime;
}
