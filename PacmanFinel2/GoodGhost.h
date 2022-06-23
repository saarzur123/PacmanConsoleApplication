#pragma once
//#include "NoviceGhost.h"
#include "SmartGhost.h"

class GoodGhost: public SmartGhost {

	int countSmartMoves = 0,countStupidMoves=0,smartMoves=0;
	
	bool is5Moves = false,isStupid=false;


public:
	GoodGhost() { figure = '$', color = Color::WHITE; }//empty ctor
	GoodGhost(int  _x, int _y) { coord.setX(_x), coord.setY(_y), figure = '$', color = Color::WHITE; }//ctor 
	virtual ~GoodGhost() {}
	void initAferDeathGhost() override;
	void moveCreature(Board& board) override; 
	void getStupid();
	bool getIs5Moves()const
	{
		return is5Moves;
	}

	bool getIsStupid()const
	{
		return isStupid;
	}

	void setIsStupid(bool val)
	{
		isStupid = val;
	}
	
};