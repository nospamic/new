#ifndef ROAD_H
#define ROAD_H

#include "iostream"
#include <conio.h>
#include <ctime>
#include "numbers.h"

class Road
{
	public:
	
		int *getRoadArray();
		
		Road();
		~Road();

	private:
		int pitStart;
		int pitEnd;
		int markingSizeY;
		int lineLength;

		void chessMarking(int position,int *roadArray);

		void addPit(int *roadArray);

		void borderLineMarking(int *roadArray);
	

};


#endif ROAD_H