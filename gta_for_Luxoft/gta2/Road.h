#ifndef ROAD_H
#define ROAD_H

#include "iostream"
#include <conio.h>
#include <ctime>
#include "numbers.h"

class Road
{
	public:
	
		int * getRoadArray();
	
	private:

		void chessMarking(int position,int *roadArray);

		void addPit(int *roadArray);
	

};


#endif ROAD_H