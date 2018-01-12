#include "Box.h"



Box::Box(int number)
{
	if (number==1){deltaX=0;}
	else{deltaX=SCR_WIDTH/2;}

	xSize=SCR_WIDTH/2;
	ySize=SCR_HEIGHT-1;
	tD1Size=xSize-10;
	tRSize=ySize-2;

	cursorPosition=0;
	isPathSaved=false;
	deltaY=0;
}


Box::~Box(void){}

bool Box::operator ==(const Box & other)
{
	bool result = true;
	if (strlen(this->currentPath)>strlen(other.currentPath))
	{
		for(unsigned i=0; i<strlen(this->currentPath);i++)
		{
			if(this->currentPath[i] != other.currentPath[i]) result=false;
		}
	}
	else
	{
		for(unsigned i=0; i<strlen(other.currentPath);i++)
		{
			if(this->currentPath[i] != other.currentPath[i]) result=false;
		}
	}
	std::cout<<result;
	return result;

}

char*Box::getCurrentDir(){return acces.getCurrentDir();}


void Box::changeDir(char*newDir){acces.changeDir(newDir);}


bool Box::isFolder(char*path){return acces.isFolder(path);}


void Box::setCursor(int Position){cursorPosition = Position;}


int Box::getCursor(){return cursorPosition;}


void Box::curToComLine(){setColor(15,0);setCur(0,ySize); }


void Box::changeDrv()
{
	SelectDrive select((xSize/2-10)+deltaX);
	currentPath=select.go(currentPath);
	SetCurrentDirectory(currentPath);
	isPathSaved = false;

	showBox();
	
}


void Box::printOneUnit()
{
	char str[SCR_WIDTH/2-2]="";
	char sign[2]="";
	int length=0;
	if (strlen(acces.unit[currentUnitPos])<tD1Size) {length=strlen(acces.unit[currentUnitPos]);}
	else {length=tD1Size;}
		
	char* unit=acces.unit[currentUnitPos];
	setCur(deltaX+2,cursorPosition+1);
	for (int n=0; n<length; n++)
	{
		sign[0]=unit[n];
		strcat(str,sign);
	}
	for(unsigned i=0; i<tD1Size-length;i++){strcat(str," ");}
	if (currentUnitPos>0 && acces.isFolder(currentUnit)){strcat(str,"  <DIR>");}
	else {strcat(str,"       ");}
	std::cout<<str;
}


void Box::printCursor(bool visible)
{
	if (isActive)
	{
		currentUnitPos=cursorPosition+deltaY;
		currentUnit = acces.unit[currentUnitPos];
		if (visible) {setColor(1,15);}
		else {setColor(15,1);}
		printOneUnit();
		curToComLine();
		//std::cout << currentPath<<unit;
	}
}

void Box::changeActive()
{
	if (isActive){isActive=false;}
	else{isActive=true;}
	showBox();
}
	

bool Box::getActive(){return isActive;}


void Box::printUnits()
{
	setColor(15,1);
	
	int nOfUnit=0;
	if (acces.unit.size()<ySize-2) {nOfUnit=acces.unit.size();}
	else {nOfUnit=ySize-2;}
	tRSize=nOfUnit;

	for (int i=0+deltaY; i<nOfUnit+deltaY; i++)
	{
		int length=0;
		if (strlen(acces.unit[i])<tD1Size) {length=strlen(acces.unit[i]);}
		else {length=tD1Size;}
		
		char* unit=acces.unit[i];
		
		for (int n=0; n<length; n++)
		{
			
			setCur(deltaX+2+n,i+1-deltaY);
			std::cout<<unit[n];
		}
		setCur(deltaX+tD1Size+4,i+1-deltaY);
		if (i>0 && acces.isFolder(acces.unit[i])){std::cout<<"<DIR>";}
	}
	setColor(15,0);
	
}


void Box::showBox()
{
	if(!isPathSaved)
	{
		currentPath=acces.getCurrentDir();
		isPathSaved=true;
	}
	acces.setUnits(currentPath);
	boxUnit=acces.unit;
	unitSize=boxUnit.size();
	namedFrame(acces.getCurrentDir(),deltaX,0,xSize,ySize);
	printUnits();
	printCursor(true);
	curToComLine();
	//std::cout<<"currentPath = "<<currentPath<<"                             \n";
}


void Box::helpLine()
{
	std::cout<<"[Up/Down]-select [Enter]-run/view [Tab]-change pannel [Space]-drive [Esc]-exit";
}


