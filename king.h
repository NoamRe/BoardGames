#pragma once

#include "stone.h"
class Player;

class King : public Stone {
public:
	//ctor:
	King(int x, int y);
	King() = default;

	//other:
	bool isCheckmate(const Board& table, Player& currPlayer, Player& otherPlayer);
	virtual void findPossibleMoves(const Board& table, Player& player);
};