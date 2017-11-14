#include "Show.h"


void Show::printRotate180()
{
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


void Show::makeVolume()
{
	setcur(0,2);
	float xExpand=0.6;
	float x2=0;
	for(int y=screenSizeY;y>=0;y--)
		{
			for(int x=0;x<screenSizeX;x++)
			{
				for(int n=0;n<2;n++)
				{
					if(screen_[x][y]==Char_BORDER){SetColor(Color_White,Color_White);}
					if(screen_[x][y]==Char_MARKING){SetColor(Color_White,Color_DarkGray);}
					if(screen_[x][y]==Char_PIT){SetColor(Color_White,Color_LightGray);}
					if (int(x2+xExpand)>int(x2))std::cout << char(screen_[x][y]);
					if(screen_[x][y]!=Char_EMPTY){SetColor(Color_White,Color_Black);}
					x2+=xExpand;
				}
			}
			std::cout <<xExpand<<"\n";
			xExpand+=0.015;
		}
}


int *Show::getCarArray(int course)
{
	int*carArray=new int[carXSize*carYSize];
	if (course==1)
	{
		carArray [0+carXSize*4]=213;carArray [1+carXSize*4]=223; carArray [2+carXSize*4]=223;carArray [3+carXSize*4]=184;
		carArray [0+carXSize*3]=179;carArray [1+carXSize*3]= 32; carArray [2+carXSize*3]= 32;carArray [3+carXSize*3]=179;
		carArray [0+carXSize*2]=186;carArray [1+carXSize*2]=219; carArray [2+carXSize*2]=219;carArray [3+carXSize*2]=186;
		carArray [0+carXSize*1]=186;carArray [1+carXSize*1]=219; carArray [2+carXSize*1]=219;carArray [3+carXSize*1]=186;
		carArray [0+carXSize*0]=212;carArray [1+carXSize*0]=205; carArray [2+carXSize*0]=205;carArray [3+carXSize*0]=190;
	}else{
		carArray [0+carXSize*0]=212;carArray [1+carXSize*0]=223; carArray [2+carXSize*0]=223;carArray [3+carXSize*0]=190;
		carArray [0+carXSize*1]=179;carArray [1+carXSize*1]= 32; carArray [2+carXSize*1]= 32;carArray [3+carXSize*1]=179;
		carArray [0+carXSize*2]=186;carArray [1+carXSize*2]=219; carArray [2+carXSize*2]=219;carArray [3+carXSize*2]=186;
		carArray [0+carXSize*3]=186;carArray [1+carXSize*3]=219; carArray [2+carXSize*3]=219;carArray [3+carXSize*3]=186;
		carArray [0+carXSize*4]=213;carArray [1+carXSize*4]=205; carArray [2+carXSize*4]=205;carArray [3+carXSize*4]=184;
	}
		
		return carArray;
}


void Show::clearAICarVector()
{
	aiXPosition.clear();
	aiYPosition.clear();
	aiCarCourse.clear();
}


void Show::resetScreen()
{
	for(int y=screenSizeY;y>=0;y--)
	{
		for(int x=0;x<screenSizeX;x++){screen_[x][y]=Char_EMPTY;}
	}
}


void Show::setAICar(int xPosition, int yPosition, int course)
{
	aiXPosition.push_back(xPosition);
	aiYPosition.push_back(yPosition);
	aiCarCourse.push_back(course);
}


void Show::infoPanel(int ySpeed, int yPosition)
{
	setcur(6,0);std::cout <<"Speed - " ;std::cout <<ySpeed*10<<" km/h  ";
	setcur(25,0);std::cout <<"Time - "  ;std::cout <<getTime()<<"   ";
	setcur(45,0);std::cout <<"Distance - ";std::cout <<int(yPosition)<<" m.   ";
}


bool Show::isCarOnScreen(int aiX, int aiY,int yPosition)
{
	int aiYMin=yPosition;
	int aiYMax=yPosition+screenSizeY;

	if(aiY>=aiYMin && aiY<=aiYMax)
		{return true;}else{return false;}
}


void Show::aiCarToScreen(int yPosition)
{
	
	for (int n=0;n<aiCarCourse.size();n++)
	{
		int aiX=aiXPosition[n];
		int aiY=aiYPosition[n];

		if (isCarOnScreen(aiX, aiY, yPosition))
		{
			int course=aiCarCourse[n];
			int *aiCarArr=getCarArray(course);
			for (int y=0; y<carYSize;y++)
			{
				for (int x=0; x<carXSize;x++)
				{
					screen_[aiX+x][(aiY-yPosition)+y]=aiCarArr[x+carXSize*y];
				}
			}

		}
	}

}


void Show::printScreen(int xPosition, int yPosition, int ySpeed, int *roadArray)
{
	int pixel;
	int *carArray=getCarArray(1);
	resetScreen();
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
	
	aiCarToScreen(int(yPosition));
	carToScreen(carArray, xPosition);
	
	infoPanel(ySpeed, yPosition);
	//makeVolume();
	printRotate180();
	

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
