#include "Game.h"


void Game::deleteArray()
{
	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		delete ghostsArr[i];
	}
		
}

//change the allocation of ghost array by user choice
void Game::initGhostsArr(Point arrGhosts[4],int size)
{
	for (int i = 0; i < size; i++)
	{
		switch (menu.getChoiceLevel())
		{
		case 1:
			ghostsArr[i] = new NoviceGhost();
			break;
		case 2:
			ghostsArr[i] = new GoodGhost();
			break;
		case 3:
			ghostsArr[i] = new SmartGhost;
			break;
		}
			ghostsArr[i]->setCurX(arrGhosts[i].getX());
			ghostsArr[i]->setCurY(arrGhosts[i].getY());
	}
}

void Game::prepareAndRunGame()
{
	if (boardRunGame.getFiles().empty())//there are no files in directory
	{
		cout << "There are no game boards to charge in file, please enter game board file to start playing!" << endl
			<< "Press any key to go back to menu" << endl;
		_getch();
	}
	else
	{
		int i = 0;
		pacman.setLives(3);
		//pass from one board to another if winning, if we didnt loose and are screens ain't over
		while (((i < boardRunGame.getFiles().size()) && (isGameRun || isWon)))
		{

			if (!boardRunGame.buildBoardFromFile(boardRunGame.getFiles()[i]))//enter data from file to vector board
			{
				isGameRun = false;
				continue;//if board invalid - continue to next board
			}

			i++;

			boardRunGame.setCountBoards(i);

			runGame();
		}

	}
}

void Game::gameManager()
{
	int indexFindFile = Creature::UNDEFINED;

	boardRunGame.initFiles();//get game boards files from directory		

	while (isGameRun)
	{

		menu.printAndGetMenu();
		
		boardRunGame.setCountBoards(0);

		switch (menu.getChoiceMenu())
		{
		case 1:
			isColored = false;
			menu.printAndGetLevelGhost();            
			prepareAndRunGame();			
			setIsGameRun(true);
			
			break;
		case 2:
			isColored = true;
			menu.printAndGetLevelGhost();
			prepareAndRunGame();			
			setIsGameRun(true); 
		
			break;
		case 3:

			menu.enterYourBoard();
			menu.printAndGetLevelGhost();

			if (findFileInArr(menu.getUserFile(),indexFindFile))
			{
				if (boardRunGame.buildBoardFromFile(boardRunGame.getFiles()[indexFindFile]))//enter data from file to vector board
				{
					boardRunGame.setCountBoards(1);
					runGame();
				}
			}

			setIsGameRun(true);
			
			break;
		case 8:
			menu.printInstructions();
			break;
		case 9:
			setIsGameRun(false);

		}
	}
}

bool Game::findFileInArr(string fileName,int & indexFindFile)
{
	size_t find;

	for (int i = 0; i < boardRunGame.getFiles().size(); i++)
	{
		find = boardRunGame.getFiles()[i].find(fileName); //find only the name string in path string
		if (find !=string::npos) 
		{
			indexFindFile = i;
			return true;
		}
	}
	isGameRun = false;
	do {
		cout << "Board was not found" << endl;
	} while (!_getch());
	return false;
}

void Game::initGame()
{
	isWon = false;
	isGameRun = true;

	pacman.setCurX(boardRunGame.getPacmanPos().getX());
	pacman.setCurY(boardRunGame.getPacmanPos().getY());
	pacman.setCurDir(Creature::UNDEFINED);
	pacman.setPrevDir(Creature::UNDEFINED);

	initGhostsArr(boardRunGame.getGhostsPos(), boardRunGame.getCountGhosts());//allocate the right level of ghosts

	numOfIterations = 0;
	pacman.setScore(0);
	pacman.setScoreWithBonus(0);
}

bool Game::isPacmanMeetGhost()const
{
	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		if ((pacman.getCurX() == ghostsArr[i]->getCurX()) && (pacman.getCurY() == ghostsArr[i]->getCurY()))
			return true;
	}

	return false;
}

void Game::statusLive()
{
	// if pacman and one of the ghosts are on the same place
	if (isPacmanMeetGhost())
	{
		afterDeathInitialization();

		pacman.decreaseLives();

		if (pacman.getLives() == 0) // game over
		{
			clear_screen();
			gotoxy(40, 12);
			std::cout << "YOU LOSE ... G A M E   O V E R !!! :-(";

			_getch();
			
			setIsGameRun(false); //end lives, back to menu
			
		}
	}

	if (getIsGameRun())
	{
		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY() + 1);
		hideCursor();
		std::cout << "                    ";

		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY()+1);
		setTextColor(fruit.getColor());
		std::cout << "LIVES:";
		for (int i = 0; i < pacman.getLives(); i++)
			std::cout << figure;
	}
	
}

void Game::statusScore()
{
	if (pacman.getScore() ==boardRunGame.getBreadCrunbs())
	{
		
		clear_screen();
		gotoxy(20, 12);
		std::cout << "CONGRATULATIONS ! Y O U  WON BOARD NUMBER "<<boardRunGame.getCountBoards()<<" ! ! !  (press any key to continue)" << endl;
		_getch();
		clear_screen();

		isWon = true;
		setIsGameRun(false); //start again
	}

	// if there is a food, increase the score
	if (boardRunGame.getMatGame(pacman.getCurY(), pacman.getCurX()) == '.')
	{
		pacman.increaseScore();
		pacman.increaseBonusScore();
	}


	if (getIsGameRun())
	{
		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY());
		setTextColor(pacman.getColor());
		std::cout << "SCORE: " << pacman.getScoreWithBonus();
	}
}

void Game::afterDeathInitialization()
{
	//update the board
	for(int i=0;i<boardRunGame.getCountGhosts();i++)
		ghostsArr[i]->draw(boardRunGame.getMatGame(ghostsArr[i]->getCurY(), ghostsArr[i]->getCurX()), boardRunGame.getColorFood());
	
	//returns pacman and the ghosts to starting position
	pacman.erase();
	pacman.setCurX(boardRunGame.getPacmanPos().getX());
	pacman.setCurY(boardRunGame.getPacmanPos().getY());

	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		ghostsArr[i]->setCurX(boardRunGame.getGhostsPos()[i].getX());
		ghostsArr[i]->setCurY(boardRunGame.getGhostsPos()[i].getY());
		ghostsArr[i]->draw(ghostsArr[i]->getFigure(), ghostsArr[i]->getColor());
		ghostsArr[i]->setCounter(0);
		ghostsArr[i]->initAferDeathGhost();		
	}
	
} 

void Game::updateColor()
{
	// if the user chose to play with color 
	if (isColored)
	{
		pacman.setColor(Color::YELLOW);
		boardRunGame.setColorWall(Color::CYAN);
		boardRunGame.setColorFood(Color::GREEN);
		fruit.setColor(Color::LIGHTRED);
	}
	else
	{
		pacman.setColor(Color::WHITE);
		boardRunGame.setColorWall(Color::WHITE);
		boardRunGame.setColorFood(Color::WHITE);
		fruit.setColor(Color::WHITE);
	}

}



void Game::runGame()
{
	
	updateColor();
		
	initGame();
	gotoxy(0, 0); // start from the right up corner
    boardRunGame.printBoard();
	

	while (isGameRun)
	{

		pacman.moveCreature(boardRunGame);
		
		statusScore();

		if (numOfIterations % 2 == 0) { //every 2 steps of pacaman, the ghost and the fruit does 1 step - half pacman's speed

			for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
			{

				if (menu.getChoiceLevel() != 1)
				{
					ghostsArr[i]->checkBestDirection(boardRunGame, pacman.getCurY(), pacman.getCurX());
				}

				ghostsArr[i]->moveCreature(boardRunGame);
			}

			fruit.moveFruit(pacman, boardRunGame, ghostsArr, numOfIterations);
		}
		

		
		statusLive();

		Sleep(500);
		numOfIterations++;//increase number of iterations
	}
	deleteArray();
}

