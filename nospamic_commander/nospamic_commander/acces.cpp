#include "acces.h"


Acces::Acces(void)
{
}


Acces::~Acces(void)
{
}


bool Acces::isFolder(char* dir)
{
	if((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(dir)) == FILE_ATTRIBUTE_DIRECTORY)
	{
		std::cout<<"<DIR>";
		return true;
	}else
	{
		return false;
	}
}


void Acces::setUnits()
{
	unit.clear();
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile("./*", &f);
	if(h != INVALID_HANDLE_VALUE)
	{
		char *un = new char;
		while(FindNextFile(h, &f))
		{
			un=f.cFileName;
			int length=strlen(un);
			char * constructUnit = new char[length];
			for (int i=0; i<=length;i++)
			{
				constructUnit[i]=*un;
				un++;
			}
			unit.push_back(constructUnit);
		} 
	}
	else
	{
		fprintf(stderr, "Error opening directory\n");
	}
}


char* Acces::getCurrentDir()
{
	const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
    GetCurrentDirectory(bufferSize, oldDir);
	
	char * constructUnit = new char[bufferSize];
	for (int i=0; i<=bufferSize;i++)
	{
		constructUnit[i]=oldDir[i];
	}
	return constructUnit;
}


void Acces::changeDir(char*newDir)
{
	SetCurrentDirectory(newDir);
	//chdir (newDir);
}


void Acces::changeDrive(unsigned int drive)
{
	_chdrive (drive);
}


unsigned int Acces::getCurrentDrive()
{
return _getdrive ();
}