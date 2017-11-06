#ifndef ROAD_H
#define ROAD_H


class Road
{
	public:
	
		int * getRoadArray();
	
	private:

		void chessMarking(int position,int *roadArray);

		void addPit(int *roadArray);
	

};


#endif ROAD_H