#include "amazonsGame.h"

//ctor:
AmazonsGame::AmazonsGame() try : Game(gameBoard = new AmazonsBoard)
{
	playerOne.setStonesLeft(STARTING_AMOUNT_OF_STONES);
	playerTwo.setStonesLeft(STARTING_AMOUNT_OF_STONES);
}
catch (bad_alloc& ex) {
	cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
	exit(1); //no need to free anything
}

//load from file ctor:
AmazonsGame::AmazonsGame(istream& inFile) : Game(inFile) {}

//other:
void AmazonsGame::makeMove(const Position& moveFrom, Position& moveTo)
{
	Players currentPlayer = static_cast<Players>(getCurrTurn());
	cout << "Please enter coordinates to make wall in:" << endl;
	Position makeWall;
	cin >> makeWall;
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
	if (!makeWall.isInTable(*gameBoard))
	{
		string error = "Your wall position is out of the game's boundaries!\n\n";
		throw out_of_range(error);
	}

	char currC = gameBoard->getCellValue(moveFrom);
	//position is in boundaries

		//checking validity:
	if (currentPlayer == Players::PLAYER1) //player with white stones ('O')
	{
		if (currC != AMAZONS_WHITE)
		{
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}

	}
	else if (currentPlayer == Players::PLAYER2)//player with black stones ('X')
		if (currC != AMAZONS_BLACK) {
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}
	//stone is valid:

	Stone& currStone = getCurrPlayer().getStoneByPos(moveFrom);
	if (!currStone.findPosInPossibleMoves(moveTo))// not available source position
	{
		string error = "The stone can't move to the position you chose!\n\n";
		throw range_error(error);
	}
	// else, move is valid:

	currStone.setPos(moveTo);
	gameBoard->setCellValue(moveFrom, moveTo);
	if (!moveTo.findPosInRisks(*gameBoard, makeWall)) //wall isn't valid
	{
		//resetting stone position:
		currStone.setPos(moveFrom);
		gameBoard->setCellValue(moveTo, moveFrom);
		string error = "The position " + static_cast<string>(makeWall) + " cant be market with a wall!\n\n";
		throw invalid_argument(error);
	}
	//else, the stone position is valid:
	dynamic_cast<AmazonsBoard&>(*gameBoard).setWall(makeWall);
	cout << "A move has been made!\n\n";

	getCurrPlayer().initStonesInList(*gameBoard, getOtherPlayer());//update stone list of player 2
	getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());// update stone list of player 1

	getCurrPlayer().setStonesLeft(getCurrPlayer().getMoveableStones());
	getOtherPlayer().setStonesLeft(getOtherPlayer().getMoveableStones());

	if (getCurrPlayer().getStonesLeft() == 0)//no more moves for player 1 -> make player 2 as winner
		getOtherPlayer().setWinner();
	if (getOtherPlayer().getStonesLeft() == 0)//no more moves for player 2 -> make player 1 as winner
		getCurrPlayer().setWinner();

	//changing turns:
	changeCurrTurn();

	//checking winner:
	if (getCurrPlayer().getStatus() && getOtherPlayer().getStatus())//if both player have no moveable stones -> draw
	{
		cout << "The game is a draw!\n\n";
		setFinished();
	}
	else
		checkWinner();
}
