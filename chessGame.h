#pragma once

#include "game.h"
#include "chessBoard.h"

class ChessGame : public Game {
public:
	//ctor:
	ChessGame();

	//load from file ctor:
	ChessGame(istream & inFile);

	//other:
	void makeMove(const Position& moveFrom, Position& moveTo);

private:
	const int STARTING_AMOUNT_OF_STONES = 16;
};

