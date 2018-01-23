#pragma once
class Unit
{
public:
	Unit(void);
	~Unit(void);

	char* name;
	char* path;

	enum UnitTipe{File, Dir, Drive, UpLevel};


};

