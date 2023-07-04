#pragma once

#include "stone.h"
class Player;

class Queen : public Stone {
public:
	//ctor:
	Queen(int x, int y);
	Queen() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};