#include "damkaBoard.h"

//ctor:
DamkaBoard::DamkaBoard() {
	LEN = DAMKA_LENGTH;

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
			if (i == 0 && (j % 2))
				table[i][j] = DAMKA_BLACK;
			else if (i == 1 && !(j % 2))
				table[i][j] = DAMKA_BLACK;
			else if (i == 2 && (j % 2))
				table[i][j] = DAMKA_BLACK;

			else if (i == (LEN - 3) && !(j % 2))
				table[i][j] = DAMKA_WHITE;
			else if (i == (LEN - 2) && (j % 2))
				table[i][j] = DAMKA_WHITE;
			else if (i == (LEN - 1) && !(j % 2))
				table[i][j] = DAMKA_WHITE;

			else
				table[i][j] = SPACE;
		}
	}
}

//load from file ctor:
DamkaBoard::DamkaBoard(istream& inFile) : Board(inFile) {}
