#pragma once

#include "board.h"
#include "player.h"
#include <fstream>

enum class GameType { DamkaGame = 1, AmazonsGame, ChessGame };


class Game {
public:
	//ctor:
	Game(Board* table);

	//load from file ctor:
	Game(istream& inFile);

	//copy ctor:
	Game(Game& other);

	//move ctor:
	Game(Game&& other) noexcept;

	//dtor:
	virtual ~Game();

	//getters:
	Board& getBoard();
	Player& getCurrPlayer();
	Player& getOtherPlayer();
	bool getIsFinished() const;
	int getCurrTurn() const;

	//setters:
	void changeCurrTurn();//change turn after move
	void setFinished();//make game finished if player won or it's a draw

	//operators:
	void operator=(Game& other);

	//other:
	void print() const;
	void checkWinner();
	virtual void makeMove(const Position& moveFrom, Position& moveTo) = 0;


	//load and save:
	void saveCurrGame() const;
	void loadCurrGame(istream& inFile);

protected:
	bool isFinished;//assign end of game
	int currTurn; //who's turn is it, 1=player 1, 2=player 2
	Board* gameBoard;
	Player playerOne, playerTwo; //data of player one and two
};