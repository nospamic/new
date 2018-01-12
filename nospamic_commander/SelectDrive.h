#pragma once
#include <vector>
#include <direct.h>
#include "console_tools.h"
#include "numbers.h"

using namespace std;

class SelectDrive
{
 
public:
	enum result {RESULT_NONE, RESULT_CHANGE, RESULT_CANSOLE};
	char* go(char* oldPath);
	
	
	SelectDrive(int xPosition);
	~SelectDrive(void);

private:
	vector<int>id;
	vector<char*>drive;
	vector<char*>type;

	int winWidth;
	int winHeight;
	int winXPosition;
	int winYPosition;
	int currentId;


	void print();
	int control();
	

	
};

