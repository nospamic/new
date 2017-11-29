#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <direct.h>


class Acces
{
public:
	std::vector<char*>unit;
	
	Acces(void);
	~Acces(void);

	bool isFolder(char*path);
	void setUnits(char*path);
	char* getCurrentDir();
	unsigned int getCurrentDrive();
	void changeDir(char*newDir);
	void changeDrive(unsigned int drive);
private:

};

