#include "acces.h"


Acces::Acces(void)
{
}


Acces::~Acces(void)
{
}


//Acces::Acces(const Acces &other)
//{
//	
//	
//	for(int i=0; i<other.unitSize; i++)
//	{
//		int length= std::strlen(other.unit[i]);
//		char*un = new char[length+1];
//		std::strcpy(un,other.unit[i]);
//		this->unit.push_back(un);
//		std::cout<<&other.unit[i]<<"-->"<<this->unit[i]<<"\n";
//	}
//}


int Acces::fileSize(char* path)
{
	std::fstream file(path);
    int size = 0;
    file.seekg (0, std::ios::end);
    size = file.tellg();
    //std::cout << "File size: " << size << " byte" ;
    file.close();
	return size;
}




char * Acces::getExtantion (char * const path) 
{
	char*pext;
	static char ext[4];
	unsigned length=strlen(path);
	for (unsigned i=length-3, n=0;i<length;i++,n++) ext[n]=path[i];
	ext[3]='\0';
	pext=ext;
	//std::cout<<pext;
	return pext;
}





bool Acces::isFolder(char* dir)
{
	if((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(dir)) == FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
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
	//std::cout<<getExtantion("asd.exe")<<"\n";system("pause");
	clearUnit();
	changeDir(path);
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile("./*", &f);
	if(h != INVALID_HANDLE_VALUE)
	{
		
		while(FindNextFile(h, &f))
		{
			const char *un = f.cFileName;
			int length=strlen(un);
			char * constructUnit = new char[length+1];
			strcpy( constructUnit, un );
			unit.push_back(constructUnit);
			constructUnit = nullptr;
		}
		unitSize=unit.size();
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

void Acces::getAllDrives()
{
	char buf[26];
    GetLogicalDriveStringsA(sizeof(buf),buf);
    
	char *DRF [] = {"Unknown" , "Invalid path",
        "Removable", "Fixed" , "Network drive","CD-ROM", "RAM disk"};
    
	for(char *s=buf; *s; s+=strlen(s)+1)
	{
         std::cout<<s<<"   "<<DRF[GetDriveTypeA(s)]<<"\n";
	}
}