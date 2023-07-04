#include "board.h"
#include "position.h"
#include "damkaBoard.h"
#include "chessBoard.h"
#include "amazonsBoard.h"

//ctor:
Board::Board() : LEN(-1) {}
Board::Board(istream& inFile)
{
	this->loadBoard(inFile);
}


//copy ctor:
Board::Board(const Board& other) {
	*this = other;
}

//move ctor:
Board::Board(Board&& other) noexcept : table(other.table) {
	LEN = other.LEN;
}

//dtor:
Board::~Board() {
	//delete the array:
	for (int i = 0; i < LEN; ++i)
		table.at(i).clear();
	table.clear();
}

//getters:
char Board::getCellValue(const Position& pos) const
{
	return table.at(pos.getX()).at(pos.getY());
}

const int Board::getLength() const {
	return LEN;
}

//setters:
void Board::setCellValue(const Position& moveFrom, const Position& moveTo)
{
	table.at(moveTo.getX()).at(moveTo.getY()) = table.at(moveFrom.getX()).at(moveFrom.getY());
	table.at(moveFrom.getX()).at(moveFrom.getY()) = SPACE;
}

void Board::setCellValue(const char newValue, const Position& pos) {
	table.at(pos.getX()).at(pos.getY()) = newValue;
}

//operators:
void Board::operator=(const Board& other) {
	if (this != &other) {
		LEN = other.LEN;
		table = other.table;
	}
}

ostream& operator<<(ostream& os, const Board& table)
{
	int currLen = table.getLength();
	for (int i = 0; i < currLen + 1; i++)
		os << "+----";
	os << '+' << endl;

	for (int i = 0; i < currLen + 1; i++) {
		if (i == 0)
			os << "|    ";
		else if (i == currLen)
		{
			if (currLen >= 10)
			{
				os << "| " << i;
			}
			else
			{
				os << "| " << i << " ";
			}
		}

		else {
			os << "|  " << i << " ";
		}
	}
	os << " |" << endl;

	for (int i = 0; i < currLen + 1; i++)
		os << "+----";
	os << '+' << endl;

	for (int row = 0; row < currLen; row++) {
		for (int col = 0; col < currLen + 1; col++) {
			if (row == (currLen - 1) && col == 0)
			{
				if (row >= 9)
				{
					os << "| " << (row + 1) << " ";
				}
				else
				{
					os << "|  " << (row + 1) << " ";
				}
			}
			else if (col == 0)
				os << "|  " << (row + 1) << " ";
			else
				os << "| " << table.getCellValue(Position(row, col - 1)) << "  ";
		}
		os << "|" << endl;
		for (int i = 0; i < currLen + 1; i++)
			os << "+----";
		os << '+' << endl;
	}

	return os;
}

//load and save:
void Board::saveBoard(ostream& outFile) const
{
	BoardType type;

	if (typeid(*this) == typeid(ChessBoard))
		type = BoardType::ChessBoard;

	if (typeid(*this) == typeid(DamkaBoard))
		type = BoardType::DamkaBoard;

	if (typeid(*this) == typeid(AmazonsBoard))
		type = BoardType::AmazonsBoard;

	outFile.write(rcastcc(&type), sizeof(BoardType));
	outFile.write(rcastcc(&LEN), sizeof(int));
	for (int i = 0; i < LEN; ++i)
	{
		for (int j = 0; j < LEN; ++j)
		{
			outFile.write(rcastcc(&table.at(i).at(j)), sizeof(char));
		}
	}
	if (!outFile.good())
	{
		string error = "Error saving to file!\n";
		throw logic_error(error);
	}
}

void Board::loadBoard(istream& inFile)
{
	inFile.read(rcastc(&LEN), sizeof(int));
	try {
		table.resize(LEN);
	}
	catch (bad_alloc &ex){
		cout << "Allocation Error: " << ex.what();
		exit(1);
	}
	for (int i = 0; i < LEN; ++i)
	{
		try {
			table.at(i).resize(LEN);
		}
		catch (bad_alloc& ex) {
			cout << "Allocation Error: " << ex.what();
			exit(1);
		}
		for (int j = 0; j < LEN; ++j)
		{
			inFile.read(rcastc(&table.at(i).at(j)), sizeof(char));
		}
	}
}