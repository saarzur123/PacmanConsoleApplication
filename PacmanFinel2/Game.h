#pragma once
#include "Menu.h"
#define PH_SIZE 4


class Game {
	
	bool isGameRun = true, isWon = false,isColored=false;
	char figure = 3;
	int lives=3,numOfIterations=0;
	Board boardRunGame;
	Pacman pacman;
	Fruit fruit;
	Creature* ghostsArr[4]= { nullptr };
	Menu menu;

public: 
	Game() {};// empty ctor
	//ctor
	Game(Pacman _pacman, Fruit _fruit) : pacman(_pacman), fruit(_fruit) {};
	~Game() {};
	bool isPacmanMeetGhost()const;
	void initGhostsArr(Point arrGhosts[4],int size);
	void runGame(); // the functions that runs all the gama
	void gameManager(); // 
	void initGame(); //initliaze the features game
	void statusLive(); // updtade current number of lives
	void statusScore(); // updtade current number of scores
	void afterDeathInitialization();//when user lose
	void updateColor();//update colors
	void deleteArray();
	bool findFileInArr(string fileName, int& indexFindFile);
	void prepareAndRunGame();

	void setIsGameRun(bool value)
	{
		isGameRun = value;
	}
	int getIsGameRun()const
	{
		return isGameRun;
	}

};
