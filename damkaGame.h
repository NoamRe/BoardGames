#pragma once

#include "game.h"

class DamkaGame : public Game
{
public:
	//ctor:
	DamkaGame();

	//load from file ctor:
	DamkaGame(istream & inFile);

	//other:
	void makeMove(const Position& moveFrom, Position& moveTo);

private:
	const int STARTING_AMOUNT_OF_STONES = 12;
};

