#pragma once

#include "stone.h"

class Player {
public:
	//ctor:
	Player(Players player, const Board& table, int maxStones = -1);
	Player() = default;

	//dtor:
	~Player();

	//getters:
	bool getStatus() const;//get status of current player(winner or not)
	int getStonesLeft() const;
	int getMoveableStones() const;

	list<Stone*>& getStoneList();
	Stone& getStoneByPos(const Position& pos);

	//setters:
	void setWinner();
	void setStonesLeft(const int stones);
	void decreaseStonesLeft();

	//other:
	void initStonesInList(const Board& table, Player& player);//initiallize stones with updated data
	void removeStoneByPos(const Position& pos);//remove stone after eat
	bool isCheck(const Board& table);
	bool isCheckmate(const Board& table, Player& currPlayer, Player& otherPlayer);
	vector<Position> findRisksInList(const Position& pos);		//check valid moves, risks 
	bool isStoneInListByPos(const Position& pos);				//check valid moves, risks
	bool isPosInPossibleMovesOfAnyStone(const Position& pos);	//check valid moves, risks

	//load and save:
	void savePlayer(ostream & outFile)const;
	void loadPlayer(istream& inFile, bool isAmazon);

private:
	int stonesLeft;
	bool isWinner;
	Players _player;
	list<Stone*> stones;

	//internal functions:
	void addChess(int boardLength, const Board& table);
	void addDamka(int boardLength, const Board& table);
	void addAmazons(int boardLength, const Board& table);
};