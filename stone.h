#pragma once

#include "board.h"
#include "Position.h"
class Player;

class Stone {
public:
	//ctor:
	Stone() = default;

	//copy ctor:
	Stone(const Stone& other);

	//move ctor:
	Stone(Stone&& other);

	//dtor:
	~Stone();// delete posible moves array

	//getters:
	const Position& getPos() const;
	Position getPos();
	int getPossibleMovesSize() const;

	//setters:
	void setPos(const Position& currPos);

	//operators:
	void operator=(const Stone& other);

	//other:
	void init(const Board& table, Player& player);// update all stones after making a move(possibleMoves)
	void printPossibleMoves() const;
	bool findPosInPossibleMoves(const Position& moveToPos);//check if new position is availble

	virtual void findPossibleMoves(const Board& table, Player& list) = 0;//allocate according to size from "findPossibleMoves"
	const Position getPosInPossibleMoves(const Position& pos) noexcept(false);

	//load and save
	void saveStone(ostream& outFile) const;
	void loadStone(istream& inFile);

protected:

	Position pos;// current position with row,col
	vector<Position> possibleMoves;
};