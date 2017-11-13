#pragma once
#include <vector>

class AIcar
{
	private:

		int xSize;
		int ySize;
		std::vector<int>roadSnapshot;

		float ySpeed;
	
		bool isPit(int *roadArray);

		bool isPitRight(int *roadArray);

		bool isPitLeft(int *roadArray);
	

	public:
		int xPosition;
		float yPosition;
		float xSpeed;
		int viewDistance;
		int xStartPosition;
		int yStartPosition;
		int course;
		int finishPosition;

	

		AIcar(int xStart, int yStart);

		int xMove(int *roadArray);

		int yMove(int *roadArray);

		bool isCrash(int *screenArray);

		void reset();

		void carShadow(int *roadArray);

		void carShadowRemove(int *roadArray);

};

