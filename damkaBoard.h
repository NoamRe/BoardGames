#pragma once

#include "board.h"

const char DAMKA_WHITE = 'o';
const char DAMKA_BLACK = 'x';
const char DAMKA_WHITE_KING = 'O';
const char DAMKA_BLACK_KING = 'X';

class DamkaBoard : public Board {
public:
	//ctor:
	DamkaBoard();

	//load from file ctor:
	DamkaBoard(istream& inFile);

private:
	const int DAMKA_LENGTH = 8;
};