#include "chessBoard.h"

//ctor:
ChessBoard::ChessBoard() {
	LEN = CHESS_LENGTH;

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
			if (i == 0) {
				switch (j) {
				case 0: table.at(i).at(j) = CHESS_BLACK_ROOK; break;
				case 1: table.at(i).at(j) = CHESS_BLACK_KNIGHT; break;
				case 2: table.at(i).at(j) = CHESS_BLACK_BISHOP; break;
				case 3: table.at(i).at(j) = CHESS_BLACK_QUEEN; break;
				case 4: table.at(i).at(j) = CHESS_BLACK_KING; break;
				case 5: table.at(i).at(j) = CHESS_BLACK_BISHOP; break;
				case 6: table.at(i).at(j) = CHESS_BLACK_KNIGHT; break;
				case 7: table.at(i).at(j) = CHESS_BLACK_ROOK; break;
				}
			}
			else if (i == 1)
				table.at(i).at(j) = CHESS_BLACK_PAWN;

			else if (i == (LEN - 2))
				table.at(i).at(j) = CHESS_WHITE_PAWN;

			else if (i == (LEN - 1))
				switch (j) {
				case 0: table.at(i).at(j) = CHESS_WHITE_ROOK; break;
				case 1: table.at(i).at(j) = CHESS_WHITE_KNIGHT; break;
				case 2: table.at(i).at(j) = CHESS_WHITE_BISHOP; break;
				case 3: table.at(i).at(j) = CHESS_WHITE_QUEEN; break;
				case 4: table.at(i).at(j) = CHESS_WHITE_KING; break;
				case 5: table.at(i).at(j) = CHESS_WHITE_BISHOP; break;
				case 6: table.at(i).at(j) = CHESS_WHITE_KNIGHT; break;
				case 7: table.at(i).at(j) = CHESS_WHITE_ROOK; break;
				}

		}
	}
}

//load from file ctor:
ChessBoard::ChessBoard(istream& inFile) : Board(inFile) {}
