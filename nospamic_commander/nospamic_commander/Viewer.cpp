#include "Viewer.h"


Viewer::Viewer(char*path)
{
	this->path=path;
	deltaX=0;
	deltaY=0;
	strCount=0;
	scrSizeX=SCR_WIDTH-2;
	scrSizeY=SCR_HEIGHT-3;
}


Viewer::~Viewer(void){}


bool Viewer::control()
{
	unsigned key1;
	if(_kbhit())
	{
		key1=_getch();
		
		if (key1 == KEY_UP && deltaY>0) 
		{
			--deltaY;
			printText();
		}
	
		if (key1 == KEY_DOWN && deltaY+scrSizeY<strCount) 
		{
			++deltaY;
			printText();
		}

		if (key1==KEY_ESCAPE){return false;}
	}
	return true;
}


void Viewer::frame()
{
	namedFrame(path,0,0,SCR_WIDTH,SCR_HEIGHT-1);
}


void Viewer::setText()
{
	std::ifstream file(path);
	if(!file.is_open()){std::cout<<"Open error";}
	
	std::string str;
	strCount=0;
	while(!file.eof())
	{
		str="";
		getline(file,str);
		text.push_back(str);
		strCount++;
	}
	file.close();
}


void Viewer::printText()
{
	setColor(15,1);
	int i=deltaY;
	while(i<deltaY+scrSizeY && i<strCount)
	{
		setCur(1,i-deltaY+1);
		std::string strFragm = text[i].substr(deltaX,deltaX+scrSizeX);
		int spaces=scrSizeX-strFragm.size();
		std::cout<<strFragm;
		for(int n=0; n<spaces; n++){std::cout<<" ";}
		i++;
	}
	setColor(15,0);
}


void Viewer::loop()
{
	frame();
	
	//int fileSize=acces.fileSize(path);
	
	setText();

	printText();

	int key=0;
	while(control()){}

}