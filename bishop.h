#pragma once

#include "stone.h"
class Player;

class Bishop : public Stone {
public:
	//ctor:
	Bishop(int x, int y);
	Bishop() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};