#pragma once

#include "game.h"
#include "amazonsBoard.h"

class AmazonsGame : public Game
{
public:
	//ctor:
	AmazonsGame();

	//load from file ctor:
	AmazonsGame(istream & inFile);

	//other:
	void makeMove(const Position& moveFrom, Position& moveTo);
private:
	const int STARTING_AMOUNT_OF_STONES = 4;
};

