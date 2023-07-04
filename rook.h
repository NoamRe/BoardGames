#pragma once

#include "stone.h"
class Player;

class Rook : public Stone {
public:
	//ctor:
	Rook(int x, int y);
	Rook() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};