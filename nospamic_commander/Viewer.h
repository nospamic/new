#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Acces.h"
#include "numbers.h"
#include "console_tools.h"


class Viewer
{
	Acces acces;
public:
	
	Viewer(char*path);
	~Viewer(void);


	
	void loop();

private:
	char*path;
	int strCount;
	int deltaX;
	int deltaY;
	int maxStrSize;
	int scrSizeX;
	int scrSizeY;
	std::vector<std::string>text;
	void frame();
	bool control();
	void printText();
	void setText();

};

