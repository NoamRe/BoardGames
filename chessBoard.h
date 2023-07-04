#pragma once

#include "board.h"

const char CHESS_WHITE_QUEEN = 'q';
const char CHESS_BLACK_QUEEN = 'Q';
const char CHESS_WHITE_ROOK = 'r';
const char CHESS_BLACK_ROOK = 'R';
const char CHESS_WHITE_BISHOP = 'b';
const char CHESS_BLACK_BISHOP = 'B';
const char CHESS_WHITE_KNIGHT = 'n';
const char CHESS_BLACK_KNIGHT = 'N';
const char CHESS_WHITE_PAWN = 'p';
const char CHESS_BLACK_PAWN = 'P';
const char CHESS_WHITE_KING = 'k';
const char CHESS_BLACK_KING = 'K';

class ChessBoard : public Board {
public:
	//ctor:
	ChessBoard();

	//loaf from file ctor:
	ChessBoard(istream& inFile);

private:
	const int CHESS_LENGTH = 8;
};