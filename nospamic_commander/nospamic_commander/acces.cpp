#include "acces.h"


Acces::Acces(void)
{
}


Acces::~Acces(void)
{
}


char* Acces::getExtantion (char * path) 
{
	char*pext;
	char ext[4];
	unsigned length=strlen(path);
	
	for (int i=length-3, n=0;i<length;i++,n++) ext[n]=path[i];
	
	ext[3]='\0';
	
	pext=&ext[0];

	return pext;
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


void Acces::clearUnit()
{
if(unit.size()>0)
	{
		for(unsigned i=0; i<unit.size();i++)
		{
			char * ptr = unit[i]; delete [] ptr;
		}
	}
	unit.clear();
}


void Acces::setUnits(char*path)
{
	clearUnit();
	changeDir(path);
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile("./*", &f);
	if(h != INVALID_HANDLE_VALUE)
	{
		
		while(FindNextFile(h, &f))
		{
			const char *un =f.cFileName;
			int length=strlen(un);
			char * constructUnit = new char[length+1];
			strcpy( constructUnit, un );
			unit.push_back(constructUnit);
			constructUnit = nullptr;
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