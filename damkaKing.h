#pragma once

#include "stone.h"
class Player;

class DamkaKing : public Stone
{
public:
	//ctor:
	DamkaKing(int x, int y);
	DamkaKing() = default;

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};

