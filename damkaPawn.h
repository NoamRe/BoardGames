#pragma once

#include "stone.h"
class Player;

class DamkaPawn : public Stone
{
public:
	//ctor:
	DamkaPawn(int x, int y);
	DamkaPawn() = default;

	//setters:
	void setKing(Board& table);

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};

