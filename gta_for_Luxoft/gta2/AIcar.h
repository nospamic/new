#pragma once
#include <vector>
#include "car.h"

class AIcar : public Car
{
	private:
		
		std::vector<int>roadSnapshot;

		bool isPit(int *roadArray);

		bool isPitRight(int *roadArray);

		bool isPitLeft(int *roadArray);
	

	public:
		
		int viewDistance;
		int xStartPosition;
		int yStartPosition;

	

		AIcar(int xStart, int yStart);

		int xMove(int *roadArray);

		int yMove(int *roadArray);

		bool isCrash(int *screenArray);

		void reset();

		void carShadow(int *roadArray);

		void carShadowRemove(int *roadArray);

};

