#include "stone.h"
#include "amazonsStone.h"
#include "player.h"

//copy ctor:
Stone::Stone(const Stone& other) {
	*this = other;
}

//move ctor:
Stone::Stone(Stone&& other)
{
	pos = other.pos;
	possibleMoves = other.possibleMoves;
}

//dtor:
Stone::~Stone()
{
	possibleMoves.clear();
}

//getters:
const Position& Stone::getPos() const
{
	return pos;
}

Position Stone::getPos()
{
	return pos;
}

int Stone::getPossibleMovesSize() const {
	return possibleMoves.size();
}

//setters:
void Stone::setPos(const Position& curr)
{
	pos = curr;
}

//operators:
void Stone::operator=(const Stone& other) {
	if (this != &other) {
		pos = other.pos;
		possibleMoves.clear();
		possibleMoves = other.possibleMoves;
	}
}

//other:
void Stone::init(const Board& table, Player& player)
{
	possibleMoves.clear();
	findPossibleMoves(table, player);
}

void Stone::printPossibleMoves() const
{
	if (possibleMoves.size() == 0) {
		string error = "There are no Possible moves for stone: " + static_cast<string>(getPos());
		throw length_error(error);
	}
	else//there are possible moves
	{
		cout << "The possible moves of the stone you chose are:";
		int size = static_cast<int>(possibleMoves.size());
		for (int i = 0; i < size; ++i)
		{
			if ((i % 4) == 0)
				cout << "\n";
			cout << possibleMoves.at(i) << "\t";
		}
		cout << "\n";
	}
}

bool Stone::findPosInPossibleMoves(const Position& moveToPos)
{
	int size = static_cast<int>(possibleMoves.size());
	for (int i = 0; i < size; ++i)
	{
		if (possibleMoves.at(i) == moveToPos)
			return true;
	}
	return false;
}

const Position Stone::getPosInPossibleMoves(const Position& pos) noexcept(false) 
{
	int size = static_cast<int>(possibleMoves.size());
	for (int i = 0; i < size; ++i)
	{
		if (possibleMoves.at(i) == pos)
			return this->getPos();
	}
	//it will be there 100%
	string error = "Unexpected error occured!\n";
	throw runtime_error(error);
}

//load and save:
void Stone::saveStone(ostream& outFile) const
{
	pos.savePosition(outFile);
	// not saving possible move of each stone because its unneccesry in the file. will call for init func at load!
}

void Stone::loadStone(istream& inFile)
{
	pos.loadPosition(inFile);
}

