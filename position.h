#pragma once

#include "board.h"
class Stone;
class Player;

class Position {
public:

	//ctors: x = row, y = col
	Position(const int x, const int y);
	Position();

	//copy ctor:
	Position(const Position& other);

	//move ctor:
	Position(Position&& other) noexcept;

	//getters:
	int getX() const;//get row
	int getY() const;// get col
	Position& getRisk(Player& player); //gets only one risk, to be used only when there is one risk
	int getRisksSize(const Board& table, char cellValue);
	int getRisksSize(Player& otherPlayer);

	//setters:
	void setX(const int x);//setRow
	void setY(const int y);//setCol
	void setPos(const int x, const int y);//set whole position

	//operators:
	const Position& operator++();
	const Position& operator--();
	bool operator==(const Position& other) const;
	void operator=(const Position& other);
	friend istream& operator>>(istream& is, Position& pos);//cin to position
	friend ostream& operator<<(ostream& os, const Position& pos);//print position
	operator string() const;//convert position to string and concat it after first string



	//other:
	const bool isInTable(const Board& table) const;//check if position is in bounderies of table
	void findPossibleRisks(const Board& table, char C);
	void findPossibleRisks(Player& player); //allocate according to size from "findAmountOfRisks"
	void findPossibleRisks(const Board& table); //for Amazons
	bool findPosInRisks(const Board& table, const Position& wallPosition);

	//templates:
	template<class T>
	void printRisks(T& obj)//print array of risks
	{
		findPossibleRisks(obj);
		if (risks.size() == 0)
		{
			string error = "There are no risks for position: " + static_cast<string>(*this);
			throw length_error(error);
		}
		else //there are risks
		{	
			int size = static_cast<int>(risks.size());
			cout << "The risks of the position you chose are: ";
			for (int i = 0; i < size; i++)
			{
				if (i % 4 == 0)
					cout << "\n";
				cout << risks.at(i) << "\t";
			}
			cout << "\n";
		}
		risks.clear();
	}

	//load and save:
	void savePosition(ostream& outFile) const;
	void loadPosition(istream& inFile);

private:
	int _x;//row
	int _y;//col
	vector<Position> risks;
};
