#include "amazonsBoard.h"
#include "position.h"

//ctor:
AmazonsBoard::AmazonsBoard() {
	LEN = AMAZONS_LENGTH;

	//allocating the array:
	try {
		table.resize(LEN);
	}
	catch (exception& ex) {
		cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
		exit(1); //no need to free anything
	}
	for (int i = 0; i < LEN; ++i) {
		try {
			table.at(i).resize(LEN);
		}
		catch (exception& ex) {
			cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
			exit(1); //no need to free anything
		}
	}

	//setting up the board:
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			table.at(i).at(j) = SPACE;

			if (i == 0)
				if (j == 3 || j == 6)
					table.at(i).at(j) = AMAZONS_BLACK;

			if (i == 3)
				if (j == 0 || j == LEN - 1)
					table.at(i).at(j) = AMAZONS_BLACK;

			if (i == 6)
				if (j == 0 || j == LEN - 1)
					table.at(i).at(j) = AMAZONS_WHITE;

			if (i == LEN - 1)
				if (j == 3 || j == 6)
					table.at(i).at(j) = AMAZONS_WHITE;
		}
	}
}

//load from file ctor:
AmazonsBoard::AmazonsBoard(istream& inFile) : Board(inFile) {}

//other:
void AmazonsBoard::setWall(const Position& wall)
{
	table.at(wall.getX()).at(wall.getY()) = AMAZONS_WALL;
}