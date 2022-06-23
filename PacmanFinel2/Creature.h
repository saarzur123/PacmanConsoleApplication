#pragma once
#include "Board.h"


class Creature { //abstract class for implement game creatures

protected:
	Point coord;
	char figure,curDir=UNDEFINED,prevDir=UNDEFINED;
	Color color=Color::WHITE;
	int key = 0, countMoves = 0;
	
public:
	virtual ~Creature(){}
	enum dir { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3,UNDEFINED=-1 };
	int getDirection(const Board& gameBoard);
	virtual void initAferDeathGhost() {};
	virtual void checkBestDirection(Board& board, int pacmanCurY, int pacmanCurX) {};
	bool checkObstacle(const Board& gameBoard,int dir);
	virtual void moveCreature(Board& board) {};
	virtual void checkCreatureObs(const Board& gameBoard, int dir) {};
	
	void setCounter(int _count)
	{
		countMoves = _count;
	}
	
	int getCounter() const {
		return countMoves;
	}
	void increasCounter() {
		countMoves++;
	}

	Color getColor()const
	{
		return color;
	}
	void setColor(Color c)
	{
		color = c;

	}
	int getCurX() const
	{
		return coord.getX();
	}
	int getCurY()const
	{
		return coord.getY();
	}

	void setCurY(int _y) {
		coord.setY(_y);
	}

	void setCurX(int _x) {
		coord.setX(_x);
	}

	char getFigure()const {
		return figure;
	}

	void draw(const char ch, Color color)const
	{
		gotoxy(coord.getX(), coord.getY());
		setTextColor(color);
		std::cout << ch;
	}

	void erase() const
	{
		gotoxy(coord.getX(), coord.getY());
		std::cout << ' ';
	}
	void setKey(int _key) {
		key = _key;
	}

	int getKey() const {
		return key;
	}

	void setCurDir(int dir)
	{
		curDir = dir;
	}

	void setPrevDir(int dir)
	{
		prevDir = dir;
	}
};