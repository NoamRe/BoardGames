#include "game.h"
#include "pawn.h"
#include "queen.h"
#include "amazonsBoard.h"
#include "amazonsGame.h"
#include "chessBoard.h"
#include "chessGame.h"
#include "damkaBoard.h"
#include "damkaGame.h"




//ctor:
Game::Game(Board* table) : gameBoard(table),
playerOne(Players::PLAYER1, *gameBoard), playerTwo(Players::PLAYER2, *gameBoard),
isFinished(false), currTurn(1) {
	playerOne.initStonesInList(*gameBoard, playerTwo);
	playerTwo.initStonesInList(*gameBoard, playerOne);
}

//load from file ctor:
Game::Game(istream& inFile) 
{
	loadCurrGame(inFile);
}

//copy ctor:
Game::Game(Game& other) : playerOne(other.playerOne), playerTwo(other.playerTwo), gameBoard(nullptr) {
	isFinished = other.isFinished;
	currTurn = other.currTurn;
	*this = other;
}

//move ctor:
Game::Game(Game&& other) noexcept : playerOne(other.playerOne), playerTwo(other.playerTwo), gameBoard(other.gameBoard) {
	isFinished = other.isFinished;
	currTurn = other.currTurn;
	other.gameBoard = nullptr;
}

//dtor:
Game::~Game() {
	delete gameBoard;
}

//getters:
Board& Game::getBoard() { return *gameBoard; }

Player& Game::getCurrPlayer()
{
	return (currTurn == 1) ? playerOne : playerTwo;
}

Player& Game::getOtherPlayer() {
	return (currTurn == 1) ? playerTwo : playerOne;
}

bool Game::getIsFinished() const
{
	return isFinished;
}

int Game::getCurrTurn() const {
	return currTurn;
}

//setters:
void Game::changeCurrTurn() { (currTurn == 1) ? currTurn++ : currTurn--; }

void Game::setFinished()
{
	isFinished = true;
}



//operators:
void Game::operator=(Game& other) {
	if (this != &other) {
		isFinished = other.isFinished;
		currTurn = other.currTurn;
		playerOne = other.playerOne;
		playerTwo = other.playerTwo;
		delete gameBoard;
		try {
			if (typeid(*other.gameBoard) == typeid(ChessBoard))
				gameBoard = new ChessBoard;
			else if (typeid(*other.gameBoard) == typeid(AmazonsBoard))
				gameBoard = new AmazonsBoard;
			else if (typeid(*other.gameBoard) == typeid(DamkaBoard))
				gameBoard = new DamkaBoard;
		}
		catch (bad_alloc& ex) {
			cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
			//free everything
			exit(1);
		}
		*gameBoard = *other.gameBoard;
	}
}

//other:
void Game::print() const
{
	cout << *gameBoard;
	if (isFinished)
	{
		if (playerOne.getStatus() && playerTwo.getStatus())
		{
			cout << "The game has ended in a draw!\n\n";
		}
		else
		{
			cout << "\nThe game is finished, and the winner is: ";
			(playerOne.getStatus()) ? (cout << "Player 1!\n\n") : (cout << "Player 2!\n\n");
		}
	}
	else
	{
		cout << "\nThe game is running!\t";
		(currTurn % 2) ?
			(cout << "It is Player 1's turn. You have: " << playerOne.getStonesLeft() << " stones left.\n\n")
			: (cout << "It is Player 2's turn. You have: " << playerTwo.getStonesLeft() << " stones left.\n\n");
	}
}

void Game::checkWinner() {
	if (playerOne.getStatus())
	{
		cout << "The winner is Player 1!\n\n";
		setFinished();
	}
	if (playerTwo.getStatus()) {
		cout << "The winner is Player 2!\n\n";
		setFinished();
	}
}

//load and save:
void Game::saveCurrGame() const {
	string fileName;
	cout << "Enter file name: ";

	cin >> fileName;
	ofstream outFile(fileName.c_str(), ios::binary | ios::trunc);//trunc = delete exist file if there is with the same name
	if (!outFile.is_open())
	{
		string error = "Error creating file!\n";
		throw logic_error(error);
	}
	cout << "Saving Current game...\n\n";
	GameType type;

	if (typeid(*this) == typeid(ChessGame))
		type = GameType::ChessGame;

	if (typeid(*this) == typeid(DamkaGame))
		type = GameType::DamkaGame;

	if (typeid(*this) == typeid(AmazonsGame))
		type = GameType::AmazonsGame;

	outFile.write(rcastcc(&type), sizeof(GameType));
	outFile.write(rcastcc(&isFinished), sizeof(isFinished));
	outFile.write(rcastcc(&currTurn), sizeof(currTurn));
	gameBoard->saveBoard(outFile);
	playerOne.savePlayer(outFile);
	playerTwo.savePlayer(outFile);
	//finish saving all fields in current game
	if (!outFile.bad())
		cout << "Game saved succesfully!\n\n";
	else
	{
		string error = "Unable to save current game to file!\n\n";
		throw logic_error(error);
	}
}

void Game::loadCurrGame(istream& inFile)
{
	inFile.read(rcastc(&isFinished), sizeof(bool));
	inFile.read(rcastc(&currTurn), sizeof(int));


	BoardType type;
	bool isAmazon = false;
	inFile.read(rcastc(&type), sizeof(BoardType));

	
	if (type == BoardType::ChessBoard)
		gameBoard = new ChessBoard(inFile);

	if (type == BoardType::AmazonsBoard)
	{
		gameBoard = new AmazonsBoard(inFile);
		isAmazon = true;
	}

	if (type == BoardType::DamkaBoard)
		gameBoard = new DamkaBoard(inFile);

	playerOne.loadPlayer(inFile, isAmazon);
	playerTwo.loadPlayer(inFile, isAmazon);
}