#pragma once
#include "Fruit.h"
#define UN_DEFINED -1

class Menu {
	int choiceMenu=UN_DEFINED,choiceLevel=UN_DEFINED;
	string userFileName;
	
public:

	int getChoiceMenu()const {
		return choiceMenu;
	}

	int getChoiceLevel()const {
		return choiceLevel;
	}

	string getUserFile()const {
		return userFileName;
	}
	
	void enterYourBoard();
	void printAndGetLevelGhost();
	void printAndGetMenu();
	void printInstructions() const;
};