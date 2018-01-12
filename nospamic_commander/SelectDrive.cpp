#include "SelectDrive.h"


SelectDrive::SelectDrive(int xPosition)
{
	char buf[26];
    GetLogicalDriveStringsA(sizeof(buf),buf);
    
	char *DRF [] = {"Unknown" , "Invalid path",
        "Removable", "Fixed" , "Network drive","CD-ROM", "RAM disk"};
    
	int i=0;
	for(char *s=buf; *s; s+=strlen(s)+1)
	{
		char*ptr=new char[strlen(s)+1];
		strcpy(ptr,s);
		this->id.push_back(i);
		this->drive.push_back(ptr);
		this->type.push_back(DRF[GetDriveTypeA(s)]);
		//std::cout<<s<<"   "<<DRF[GetDriveTypeA(s)]<<"\n";
		//std::cout<<id[i]<<"  "<<drive[i]<<"  "<<type[i]<<"\n";
		i++;
	}

	//std::cout<<i;
	winWidth=18;
	winHeight=i+2;
	winXPosition=xPosition;
	winYPosition=SCR_HEIGHT/2-winHeight/2;
	currentId=0;
}



SelectDrive::~SelectDrive(void)
{
for (int i=0; i<drive.size(); i++)
	{
		char*ptr=drive[i];
		delete[] ptr;
	}
}


int SelectDrive::control()
{
	int done=RESULT_NONE;
	unsigned key;
	if(_kbhit())
	{
		key=_getch();
		if (key == KEY_ESCAPE) {done=RESULT_CANSOLE;}
		if (key == KEY_ENTER) {done=RESULT_CHANGE; SetCurrentDirectory(drive[currentId]);}
		if (key == KEY_UP && currentId>0) {currentId--; print();}
		if (key == KEY_DOWN && currentId<id.size()-1) {currentId++; print();}
	}
	return done;
}


char* SelectDrive::go(char*oldPath)
{
	setColor(15,Color_DarkGray);
	namedFrame2("Select drive",winXPosition,winYPosition, winWidth, winHeight);
	setColor(15,1);
	print();

	int done=RESULT_NONE;
	char *path;
	while(done==RESULT_NONE)
	{
		done=control();
		if (done==RESULT_CANSOLE) path=oldPath;
		if (done==RESULT_CHANGE) path=drive[currentId];
	}
	return path;
}


void SelectDrive::print()
{
	setColor(15,Color_DarkGray);
	for (int i=0; i<id.size(); i++)
	{
		setCur(winXPosition+2, winYPosition+1+i);
		id[i]==currentId?setColor(1,15):true;
		std::cout<<id[i]<<"  "<<drive[i]<<"  "<<type[i]<<"\n";
		id[i]==currentId?setColor(15,Color_DarkGray):true;
	}
	setColor(15,1);
}