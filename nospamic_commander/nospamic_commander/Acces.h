#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <direct.h>
#include <string.h>
#include <fstream>
#include <conio.h>

class Acces
{
public:
	std::vector<char*>unit;
	
	Acces(void);
	~Acces(void);
	//Acces(const Acces &other);

	bool isFolder(char*path);
	void setUnits(char*path);
	char* getCurrentDir();
	unsigned int getCurrentDrive();
	void changeDir(char*newDir);
	void changeDrive(unsigned int drive);
	char * getExtantion (char * path);
	int fileSize(char*path);
	void getAllDrives();
private:
	int unitSize;
	void clearUnit();
};

