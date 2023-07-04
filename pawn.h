#pragma once

#include "stone.h"
class Player;

class Pawn : public Stone {
public:
	//ctor:
	Pawn(int x, int y);
	Pawn() = default;

	//setters:
	void setQueen(Board& table);

	//other:
	virtual void findPossibleMoves(const Board& table, Player& player);
};