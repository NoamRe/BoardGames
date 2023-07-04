#pragma once

#include "board.h"

const char AMAZONS_WHITE = 'O';
const char AMAZONS_BLACK = 'X';
const char AMAZONS_WALL = '@';

class AmazonsBoard : public Board {
public:
	//ctor:
	AmazonsBoard();

	//load from file ctor:
	AmazonsBoard(istream& inFile);

	//other:
	void setWall(const Position& wall);

private:
	const int AMAZONS_LENGTH = 10;

};