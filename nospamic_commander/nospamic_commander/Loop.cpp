#include "Loop.h"


Loop::Loop(void):boxLeft(1),boxRight(2)//, boxActive(boxLeft)
{
	boxActive=&boxLeft;
}


Loop::~Loop(void)
{
}



void Loop::keySpace()
{
	boxActive->changeDrv();
}


void Loop::keyTab()
{
			boxLeft.changeActive();
			boxRight.changeActive();
			if (boxLeft.isActive){boxActive=&boxLeft;}
			else {boxActive=&boxRight;}
			SetCurrentDirectory(boxActive->currentPath);
}


void Loop::keyDown()
{
			if(boxActive->cursorPosition < boxActive->tRSize-1) 
			{
				boxActive->printCursor(false);
				++boxActive->cursorPosition; 
				boxActive->printCursor(true);
			}

			if(boxActive->cursorPosition==boxActive->tRSize-1 
			&& boxActive->currentUnitPos<boxActive->unitSize-1)
			{
				++boxActive->deltaY; 
				boxActive->showBox();
			}
}


void Loop::keyUp()
{
	if(boxActive->cursorPosition>0) 
	{
		boxActive->printCursor(false);
		--boxActive->cursorPosition; 
		boxActive->printCursor(true);
	}

	if(boxActive->cursorPosition==0 && boxActive->deltaY>0)
	{
		--boxActive->deltaY; 
		boxActive->showBox();
	}
	
}


void Loop::keyEnter()
{

	if(boxActive->isFolder(boxActive->currentUnit))
	{
		
		boxActive->changeDir(boxActive->currentUnit);
		boxActive->deltaY=0;
		boxActive->currentPath=boxActive->getCurrentDir();
		boxActive->cursorPosition=0;
		boxActive->showBox();
		
	}
			
	char *exe="exe";
	char *txt="txt";
	if(*acces.getExtantion(boxActive->currentUnit)==*exe && !boxActive->isFolder(boxActive->currentUnit))
	{
		//std::cout<<boxActive->currentUnit<<"                  ";
		ShellExecute(NULL, "open", boxActive->currentUnit, NULL, boxActive->currentPath, SW_SHOWNORMAL);
	}
	
	if(*acces.getExtantion(boxActive->currentUnit)!=*exe 
		&& !boxActive->isFolder(boxActive->currentUnit)
		&& acces.fileSize(boxActive->currentUnit)<4500)
	{
		Viewer view(boxActive->currentUnit);
		view.loop();
		boxLeft.showBox();
		boxRight.showBox();
		SetCurrentDirectory(boxActive->currentPath);
	}
}


void Loop::control()
{
	unsigned key1;
	if(_kbhit())
	{
		key1=_getch();
		if (key1 == KEY_ESCAPE)exit(0);
		if (key1 == KEY_ENTER) keyEnter();
		if (key1 == KEY_UP) keyUp();
		if (key1 == KEY_DOWN) keyDown();
		if (key1 == KEY_TAB && !(boxLeft == boxRight)) keyTab();
		if (key1 == KEY_SPACE) keySpace();
	}
}



void Loop::go()
{
	boxLeft.showBox();
	boxRight.changeActive();
	boxRight.showBox();
	boxActive->helpLine();

	while(true)
	{
		Sleep(20);
		control();
	}


}