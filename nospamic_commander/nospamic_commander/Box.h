#pragma once
#include "Acces.h"
#include "console_tools.h"
#include "numbers.h"
#include "SelectDrive.h"

class Box
{
Acces acces;

public:
	bool isActive;
	int cursorPosition;
	int tRSize;
	int unitSize;
	char* currentUnit;
	char* currentPath;
	bool isPathSaved;
	int deltaY;
	int currentUnitPos;
	std::vector<char*>boxUnit;
	
	Box(int number);
	~Box(void);
	bool operator ==(const Box & other);
	
	void showBox();
	void changeActive();
	bool getActive();
	void setCursor(int Position);
	int getCursor();
	bool isFolder(char*unit);
	void changeDir(char*newDir);
	char*getCurrentDir();
	void printCursor(bool visible);
	void changeDrv();
	void helpLine();

private:
	int deltaX;
	unsigned xSize;
	unsigned ySize;
	unsigned tD1Size;
	void printUnits();
	void printOneUnit();
	void curToComLine();

};

