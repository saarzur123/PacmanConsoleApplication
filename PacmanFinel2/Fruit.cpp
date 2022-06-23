#include "Fruit.h"

void Fruit::initialFruit(const Board& board)
{
	initialRandomFigure();
	initialRandomCoord(board);
	howLongFruitStay = setHowLongFruitStay();
}

void Fruit::initialRandomFigure() //select the figure between 5-9
{
	int randomFigure;

	srand(time(nullptr));
	randomFigure = rand() % 4 + 5; //every number symbolize a figure

	addScore = randomFigure;

	figure=(randomFigure+'0');

}
void Fruit::initialRandomCoord(const Board& board)//select random coordinate on screen
{
	int randomX, randomY;

	do { //the start point of fruit cant be on obstcale
		srand(time(nullptr));
		randomX = rand() % (board.getRight() - 3) + 2;

		srand(time(nullptr));
		randomY = rand() % (board.getDown() - 3) + 2;

	} while (board.getMatGame(randomX, randomY) == '#');

	coord.setX(randomX);
	coord.setY(randomY);
}

void Fruit::moveFruit(Pacman& pacman,Board& board,Creature** ghostsArr, int numOfIterations) {

	if (numOfIterations == whenFruitShow)
	{
		initialFruit(board);
		isFruitOnScreen = true;
	}

	if (isFruitOnScreen) {

		if (counterFruitIter < howLongFruitStay) // fruit shows if there is no fruit on screen and in this specific score
		{
			key = rand() % 4; //every number symbolize a direction
					
			moveCreature(board);
			isCollision(pacman, ghostsArr,board);
			counterFruitIter++;
		}
		else 
		{
			//erase
			printBeforeGhost(board);
			resetFruit();
		}

	}
}


void Fruit::moveCreature(Board &board)
{
	printBeforeGhost(board);

	while (checkObstacle(board, getDirection(board)))//choose -not wall- direction key 
	{
		curDir = rand() % 4;
		key = curDir;
	}

	moveGhost(board);
}

void Fruit::resetFruit()
{
	isFruitOnScreen = false;
	counterFruitIter = 0;
	whenFruitShow += setWhenFruitShow();
}


void Fruit::isCollision(Pacman& pacman,Creature** ghostsArr,const Board& board)
{
	if (((pacman.getCurX() == getCurX()) && (pacman.getCurY() == getCurY()))) //if pacman eat fruit he gets the food of fruit.
	{
		pacman.setScoreWithBonus(pacman.getScoreWithBonus() + addScore);
		resetFruit();
	}

	for (int i = 0; i < board.getCountGhosts(); i++)
	{
		if (((ghostsArr[i]->getCurX() == getCurX()) && (ghostsArr[i]->getCurY() == getCurY()))) //if pacman eat fruit he gets the food of fruit.
		{
			resetFruit();
			break;
		}
	}
}
