#include "GoodGhost.h"

void GoodGhost::moveCreature(Board& board) {
	
	// ghost is in his smart moves
	if (countSmartMoves == 0 && !isStupid)
	{
		countSmartMoves = rand() % 10 + 15; //randomly chosing ~20(15-25) smart moves
		smartMoves = countSmartMoves;
	}

	// ghost move 5 "stupid" steps
	if (isStupid)
	{		
		getStupid();
		printBeforeGhost(board);
		moveGhost(board);
		countStupidMoves++;

		if (countStupidMoves == 5)
		{
			countStupidMoves = 0;
			isStupid = false;
		}
	}
	else
	{
		SmartGhost::moveCreature(board);
		countSmartMoves--;
		if (countSmartMoves == 0)
			isStupid = true;
	}


}

void GoodGhost::initAferDeathGhost()
{
	setCounter(0);
	countSmartMoves = countStupidMoves = countMoves = 0;
	isStupid = is5Moves = false;
}

//get to each 5 moves same direction
void GoodGhost::getStupid() 
{
	if (getCounter() % smartMoves == 0)
	{
		is5Moves = true;
		do {
			prevDir = curDir;
			curDir = rand() % 4; //every number symbolize a direction
		} while (curDir == prevDir);
	}

	if (getCounter() % smartMoves < 5)
	{
		key = curDir;

	}
	else
		is5Moves = false;


}

