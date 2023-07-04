#pragma once

#include "stone.h"
class Player;

class AmazonsStone : public Stone
{
public:
	//ctor:
	AmazonsStone(int x, int y);
	AmazonsStone() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};

