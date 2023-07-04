#include "chessGame.h"
#include "pawn.h"
#include "queen.h"

//ctor:
ChessGame::ChessGame() try : Game(gameBoard = new ChessBoard) {
	playerOne.setStonesLeft(STARTING_AMOUNT_OF_STONES);
	playerTwo.setStonesLeft(STARTING_AMOUNT_OF_STONES);
}
catch (bad_alloc& ex) {
	cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
	exit(1); //no need to free anything
}

//load from file ctor:
ChessGame::ChessGame(istream& inFile) : Game(inFile) {}

//other:
void ChessGame::makeMove(const Position& moveFrom, Position& moveTo)
{
	Players currentPlayer = static_cast<Players>(getCurrTurn());

	if (!moveFrom.isInTable(*gameBoard))
	{
		string error = "Your starting position is out of the game's boundaries!\n\n";
		throw out_of_range(error);
	}
	if (!moveTo.isInTable(*gameBoard))
	{
		string error = "Your destination position is out of the game's boundaries!\n\n";
		throw out_of_range(error);
	}

	char currC = gameBoard->getCellValue(moveFrom);
	//position is in boundaries

		//checking validity:
	if (currentPlayer == Players::PLAYER1) //player with white stones ('O')
	{
		if ((currC != CHESS_WHITE_BISHOP) &&
			(currC != CHESS_WHITE_KING) &&
			(currC != CHESS_WHITE_KNIGHT) &&
			(currC != CHESS_WHITE_PAWN) &&
			(currC != CHESS_WHITE_QUEEN) &&
			(currC != CHESS_WHITE_ROOK)) {
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}

	}
	else if (currentPlayer == Players::PLAYER2) { //player with black stones ('X')
		if ((currC != CHESS_BLACK_BISHOP) &&
			(currC != CHESS_BLACK_KING) &&
			(currC != CHESS_BLACK_KNIGHT) &&
			(currC != CHESS_BLACK_PAWN) &&
			(currC != CHESS_BLACK_QUEEN) &&
			(currC != CHESS_BLACK_ROOK)) {
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}
	}


	//stone is valid:

	Stone& currStone = getCurrPlayer().getStoneByPos(moveFrom);
	if (!currStone.findPosInPossibleMoves(moveTo))// not available source position
	{
		string error = "The stone can't move to the position you chose!\n\n";
		throw range_error(error);
	}

	// else, move is valid:

	//first check if move is legal:
	currStone.setPos(moveTo);
	char tempC = gameBoard->getCellValue(moveTo); //save the enemy stone
	gameBoard->setCellValue(moveFrom, moveTo); //make the move on the board temporarily
	//init the other player's possible moves to account for the change:
	getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());
	//check if the curr player's king is now threatend because of the move (illegal move)
	if (getCurrPlayer().isCheck(*gameBoard))
	{
		gameBoard->setCellValue(moveTo, moveFrom); //returns the piece to where it was
		gameBoard->setCellValue(tempC, moveTo);  //return the enemy stone to where it was
		currStone.setPos(moveFrom);
		getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());
		string error = "!!!!\nILLEGAL MOVE\n!!!!\n\nThe move will be canceled.\n";
		throw invalid_argument(error);
	}

	//move is legal:
	gameBoard->setCellValue(moveTo, moveFrom); //returns the piece to where it was
	gameBoard->setCellValue(tempC, moveTo);  //return the enemy stone to where it was
	getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());

	if (gameBoard->getCellValue(moveTo) != SPACE) { //has to be another player's stone
		getOtherPlayer().removeStoneByPos(moveTo); //removes other player's stone
		getOtherPlayer().decreaseStonesLeft(); //decreases the number of stones
	}
	gameBoard->setCellValue(moveFrom, moveTo);
	cout << "A move has been made!\n\n";

	//check if queen
	if ((gameBoard->getCellValue(moveTo) == CHESS_BLACK_PAWN && moveTo.getX() == (gameBoard->getLength() - 1)) ||
		(gameBoard->getCellValue(moveTo) == CHESS_WHITE_PAWN && moveTo.getX() == 0)) {
		//makes it a queen on the board:
		dynamic_cast<Pawn&>(currStone).setQueen(*gameBoard);
		//removes the pawn from the list:
		getCurrPlayer().removeStoneByPos(moveTo);
		//adds a queen instead:
		Stone* queen = new Queen(moveTo.getX(), moveTo.getY());
		getCurrPlayer().getStoneList().push_back(queen);
		cout << "\nCongratioulations! You have a new queen at coordinate: " + static_cast<string>(moveTo) << endl;
	}
	//initialize all stones possiblemoves
	getCurrPlayer().initStonesInList(*gameBoard, getOtherPlayer());//update stone list of curr player 
	getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());// update stone list of other player 

	//CHECK IF CHECKMATE
	if (getOtherPlayer().isCheckmate(*gameBoard, getOtherPlayer(), getCurrPlayer()))
	{
		cout << "!!!!\nCheckmate!\n!!!!\n";
		getCurrPlayer().setWinner();
	}

	//CHECK IF CHECK
	else if (getOtherPlayer().isCheck(*gameBoard))
		cout << "\n!!!!\nCheck!\n!!!!\n";

	//changing turns:
	changeCurrTurn();

	checkWinner();
}
