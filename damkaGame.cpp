#include "damkaGame.h"
#include "damkaBoard.h"
#include "damkaKing.h"
#include "damkaPawn.h"

//ctor:
DamkaGame::DamkaGame() : Game(gameBoard = new DamkaBoard)
{
	playerOne.setStonesLeft(STARTING_AMOUNT_OF_STONES);
	playerTwo.setStonesLeft(STARTING_AMOUNT_OF_STONES);
}

//load from file ctor:
DamkaGame::DamkaGame(istream& inFile) : Game(inFile) {}

//other:
void DamkaGame::makeMove(const Position& moveFrom, Position& moveTo)
{
	Players startingPlayer = static_cast<Players>(getCurrTurn());

	if (!(moveFrom.isInTable(*gameBoard)))
	{
		string error = "The coordinate " + static_cast<string>(moveFrom) +" are out of the game board!\n";
		throw out_of_range(error);
	}
	if (!(moveTo.isInTable(*gameBoard)))
	{
		string error = "The coordinate " + static_cast<string>(moveTo) + " are out of the game board!\n";
		throw out_of_range(error);
	}

	char currC = gameBoard->getCellValue(moveFrom);

	if (startingPlayer == Players::PLAYER1) //O
	{
		if (currC != DAMKA_WHITE && currC != DAMKA_WHITE_KING) {
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}
	}
	else if (startingPlayer == Players::PLAYER2) //X
	{
		if (currC != DAMKA_BLACK && currC != DAMKA_BLACK_KING) {
			string error = "You have chosen invalid stone!\n";
			throw invalid_argument(error);
		}
	}

	Stone& currStone = getCurrPlayer().getStoneByPos(moveFrom);
	if (!currStone.findPosInPossibleMoves(moveTo)) {
		string error = "The stone can't move to the position you chose!\n\n";
		throw range_error(error);
	}

	else { //it can move there
		currStone.setPos(moveTo);
		Position potentialStone;
		potentialStone.setX(moveTo.getX() - (moveTo.getX() - moveFrom.getX()) / abs(moveTo.getX() - moveFrom.getX()));
		potentialStone.setY(moveTo.getY() - (moveTo.getY() - moveFrom.getY()) / abs(moveTo.getY() - moveFrom.getY()));
		gameBoard->setCellValue(moveFrom, moveTo);
		if (gameBoard->getCellValue(potentialStone) != SPACE) { //has to be another player's stone
			gameBoard->setCellValue(SPACE, potentialStone);
			getOtherPlayer().removeStoneByPos(potentialStone); //removes other player's stone
			getOtherPlayer().decreaseStonesLeft(); //decreases the number of stones
		}
	}
	cout << "A move has been made!\n\n";

	//check if king
	if ((gameBoard->getCellValue(moveTo) == DAMKA_BLACK && moveTo.getX() == (gameBoard->getLength() - 1)) ||
		(gameBoard->getCellValue(moveTo) == DAMKA_WHITE && moveTo.getX() == 0)) {
		//makes it a king on the board:
		dynamic_cast<DamkaPawn&>(currStone).setKing(*gameBoard);
		//removes the pawn from the list:
		getCurrPlayer().removeStoneByPos(moveTo);
		//adds a king instead:
		Stone* king = new DamkaKing(moveTo.getX(), moveTo.getY());
		getCurrPlayer().getStoneList().push_back(king);
		cout << "\nCongratioulations! You have a king at coordinate: " + static_cast<string>(moveTo) << endl;
	}

	//init possible moves:
	getCurrPlayer().initStonesInList(*gameBoard, getOtherPlayer());//update stone list of curr player 
	getOtherPlayer().initStonesInList(*gameBoard, getCurrPlayer());// update stone list of other player 

	if (getOtherPlayer().getStonesLeft() == 0)
		getCurrPlayer().setWinner();

	//changing turns:
	changeCurrTurn();

	checkWinner();
}
