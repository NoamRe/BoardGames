#pragma once

#include "stone.h"
class Player;

class Knight : public Stone {
public:
	//ctor:
	Knight(int x, int y);
	Knight() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};