#pragma once
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

#include <iostream>
#include <vector>
#include <string>
#include <list>
class Position;
using namespace std;
const char SPACE = ' ';
enum class Players { PLAYER1 = 1, PLAYER2 };
enum class BoardType { DamkaBoard = 1, AmazonsBoard, ChessBoard };

class Board {
public:
	//ctor:
	Board();
	Board(istream& inFile);

	//copy ctor:
	Board(const Board& other);

	//move ctor:
	Board(Board&& other) noexcept;

	//dtor:
	virtual ~Board(); //frees the array

	//getters:
	char getCellValue(const Position& pos) const;//get char value of coordinate in table
	const int getLength() const;

	//setters:
	void setCellValue(const Position& moveFrom, const Position& moveTo);
	void setCellValue(const char newValue, const Position& pos);

	//operators:
	void operator=(const Board& other);
	friend ostream& operator<<(ostream& os, const Board& table);//print operator

	//load and save:
	void saveBoard(ostream & outFile) const;
	void loadBoard(istream& inFile);

protected:
	vector<vector<char>> table;
	int LEN; //the board's length

};