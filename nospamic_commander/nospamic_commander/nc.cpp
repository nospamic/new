#include <iostream>
#include <windows.h>
#include <vector>
#include <direct.h>
#include "acces.h"
#include "Box.h"




int main()
{


	Box box1(1);
	Box box2(2);
	box1.showBox();
	box2.showBox();
	/*Acces acces;
	acces.changeDir("D:\\html_temp");
	acces.setUnits();
	
	for (int i=0; i<acces.unit.size();i++)
	{
		std::cout<<"\n"<<acces.unit[i];
		acces.isFolder(acces.unit[i]);
	}
	std::cout<<"\n\n";
	
	std::cout<<"\n"<<acces.getCurrentDir();
	std::cout << "\n Current drive is - "<< acces.getCurrentDrive()<<"\n";*/

	system("pause");
	return 0;
}