#include "player.h"
#include "king.h"
#include "chessBoard.h"
#include "amazonsBoard.h"
#include "damkaBoard.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "damkaKing.h"
#include "damkaPawn.h"
#include "amazonsStone.h"

enum class stoneType { DamkaPawn = 1, DamkaKing, AmazonsStone, Rook, Knight, Bishop, Queen, King, Pawn };


//ctor:
Player::Player(Players player, const Board& table, int maxStones) :
	stonesLeft(maxStones), _player(player), isWinner(false)
{
	//make stonelist
	int boardLength = table.getLength();
	if (typeid(table) == typeid(ChessBoard))
		addChess(boardLength, table);
	else if (typeid(table) == typeid(AmazonsBoard))
		addAmazons(boardLength, table);
	else if (typeid(table) == typeid(DamkaBoard))
		addDamka(boardLength, table);
}

//dtor:
Player::~Player() {
	//frees the stones:
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		delete (*currStone);
	}
}

//getters:
bool Player::getStatus() const
{
	return isWinner;
}

int Player::getStonesLeft() const {
	return stonesLeft;
}

int Player::getMoveableStones() const {
	int sum = 0;
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if ((*currStone)->getPossibleMovesSize() != 0)
			++sum;
	}
	return sum;
}

list<Stone*>& Player::getStoneList()
{
	return stones;
}

Stone& Player::getStoneByPos(const Position& pos) {
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if ((*currStone)->getPos() == pos)
			return *(*currStone);
	}
	string error = "Unexpected error occured!\n";
	throw runtime_error(error);
}

//setters:
void Player::setWinner()
{
	isWinner = true;
}

void Player::setStonesLeft(const int stones) {
	stonesLeft = stones;
}

void Player::decreaseStonesLeft() {
	stonesLeft--;
}

//other:
void Player::initStonesInList(const Board& table, Player& player) {
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		(*currStone)->init(table, player);
	}
}

void Player::removeStoneByPos(const Position& pos) {
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if ((*currStone)->getPos() == pos) {
			delete (*currStone);
			currStone = stones.erase(currStone);
		}
	}
}

bool Player::isCheck(const Board& table) {
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if (typeid((*(*currStone))) == typeid(King)) {
			char currC = table.getCellValue((*currStone)->getPos());
			if ((*currStone)->getPos().getRisksSize(table, currC) > 0) //the king has risks
				return true;
			else
				return false;
		}
	}
	string error = "Unexpected error occured!\n";
	throw runtime_error(error);
}

bool Player::isCheckmate(const Board& table, Player& currPlayer, Player& otherPlayer)
{
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if (typeid((*(*currStone))) == typeid(King)) {
			return (dynamic_cast<King&>((*(*currStone))).isCheckmate(table, currPlayer, otherPlayer));
		}
	}
	string error = "Unexpected error occured!\n";
	throw runtime_error(error);
}

vector<Position> Player::findRisksInList(const Position& pos) {
	vector<Position> res;
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if (typeid((*(*currStone))) == typeid(DamkaPawn) || typeid((*(*currStone))) == typeid(DamkaKing)) {
			Position temp = pos;
			Position enemyPos = (*currStone)->getPos();
			if (abs(temp.getX() - enemyPos.getX()) != 0 && abs(temp.getY() - enemyPos.getY()) != 0) {
				temp.setX(temp.getX() + (temp.getX() - enemyPos.getX()) / abs(temp.getX() - enemyPos.getX()));
				temp.setY(temp.getY() + (temp.getY() - enemyPos.getY()) / abs(temp.getY() - enemyPos.getY()));
			}
			if ((*currStone)->findPosInPossibleMoves(temp)) {
				res.push_back((*currStone)->getPosInPossibleMoves(temp));
			}
		}
		else if ((*currStone)->findPosInPossibleMoves(pos)) {
			res.push_back((*currStone)->getPosInPossibleMoves(pos));
		}
	}
	return res;
}

bool Player::isStoneInListByPos(const Position& pos)
{
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {
		if ((*currStone)->getPos() == pos)
		{
			return true;
		}
	}
	return false;
}

bool Player::isPosInPossibleMovesOfAnyStone(const Position& pos) {
	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone) {

		if ((*currStone)->findPosInPossibleMoves(pos))
			return true;
	}
	return false;
}

//load and save:
void Player::savePlayer(ostream& outFile) const
{
	outFile.write(rcastcc(&stonesLeft), sizeof(int));
	outFile.write(rcastcc(&isWinner), sizeof(bool));
	outFile.write(rcastcc(&_player), sizeof(Players));

	for (auto currStone = stones.begin(); currStone != stones.end(); ++currStone)
	{
		if (typeid(*(*currStone)) == typeid(DamkaPawn))
		{
			stoneType type = stoneType::DamkaPawn;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(DamkaKing))
		{
			stoneType type = stoneType::DamkaKing;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(AmazonsStone))
		{
			stoneType type = stoneType::AmazonsStone;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(Rook))
		{
			stoneType type = stoneType::Rook;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(Knight))
		{
			stoneType type = stoneType::Knight;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(Bishop))
		{
			stoneType type = stoneType::Bishop;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(Queen))
		{
			stoneType type = stoneType::Queen;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(King))
		{
			stoneType type = stoneType::King;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		else if (typeid(*(*currStone)) == typeid(Pawn))
		{
			stoneType type = stoneType::Pawn;
			outFile.write(rcastcc(&type), sizeof(type));
		}
		(*currStone)->saveStone(outFile);
	}
}

void Player::loadPlayer(istream& inFile, bool isAmazon)
{
	inFile.read(rcastc(&stonesLeft), sizeof(int));
	inFile.read(rcastc(&isWinner), sizeof(bool));
	inFile.read(rcastc(&_player), sizeof(Players));

	if (isAmazon)// is amazon we need to initiallize all stone even if they are stuck
		setStonesLeft(4);

	for (int i = 0; i < stonesLeft; i++)
	{
		stoneType type;
		inFile.read(rcastc(&type), sizeof(stoneType));

		if (type == stoneType::DamkaPawn)
		{
			Stone* damka;
			try {
				damka = new DamkaPawn;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			damka->loadStone(inFile);
			stones.push_back(damka);
		}
		else if (type == stoneType::DamkaKing)
		{
			Stone* damkaKing;
			try {
				damkaKing = new DamkaKing;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			damkaKing->loadStone(inFile);
			stones.push_back(damkaKing);
		}
		else if (type == stoneType::AmazonsStone)
		{
			Stone* amazonsStone;
			try {
				amazonsStone = new AmazonsStone;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			amazonsStone->loadStone(inFile);
			stones.push_back(amazonsStone);
		}
		else if (type == stoneType::Rook)
		{
			Stone* rook;
			try {
				rook = new Rook;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			rook->loadStone(inFile);
			stones.push_back(rook);
		}
		else if (type == stoneType::Knight)
		{
			Stone* knight;
			try {
				knight = new Knight;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			knight->loadStone(inFile);
			stones.push_back(knight);
		}
		else if (type == stoneType::Bishop)
		{
			Stone* bishop;
			try {
				bishop = new Bishop;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			bishop->loadStone(inFile);
			stones.push_back(bishop);
		}
		else if (type == stoneType::Queen)
		{
			Stone* queen;
			try {
				queen = new Queen;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			queen->loadStone(inFile);
			stones.push_back(queen);
		}
		else if (type == stoneType::King)
		{
			Stone* king;
			try {
				king = new King;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			king->loadStone(inFile);
			stones.push_back(king);
		}
		else if (type == stoneType::Pawn)
		{
			Stone* pawn;
			try {
				pawn = new Pawn;
			}
			catch (bad_alloc& ex) {
				cout << "Allocation Error: " << ex.what();
				exit(1);
			}
			pawn->loadStone(inFile);
			stones.push_back(pawn);
		}
	}
}

//internal functions:
void Player::addChess(int boardLength, const Board& table) {
	if (_player == Players::PLAYER1)//initiallize stones for player 1 
	{
		for (int i = (boardLength - 2); i < boardLength; ++i)
			for (int j = 0; j < boardLength; ++j) {
				try {
					if (i == (boardLength - 2)) { //all pawns
						Stone* pawn = new Pawn(i, j);
						stones.push_back(pawn);
					}
					else if (j == 0 || j == (boardLength - 1)) {
						Stone* rook = new Rook(i, j);
						stones.push_back(rook);
					}
					else if (j == 1 || j == (boardLength - 2)) {
						Stone* knight = new Knight(i, j);
						stones.push_back(knight);
					}
					else if (j == 2 || j == (boardLength - 3))
					{
						Stone* bishop = new Bishop(i, j);
						stones.push_back(bishop);
					}
					else if (j == 3)
					{
						Stone* queen = new Queen(i, j);
						stones.push_back(queen);
					}
					else if (j == 4)
					{
						Stone* king = new King(i, j);
						stones.push_back(king);
					}
				}
				catch (exception& ex) {
					cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
					exit(1); //no need to free anything
				}
			}
	}
	else //initiallize stones for player 2 
	{
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < boardLength; ++j) {
				try {
					if (i == 1) { //all pawns
						Stone* pawn = new Pawn(i, j);
						stones.push_back(pawn);
					}
					else if (j == 0 || j == (boardLength - 1))
					{
						Stone* rook = new Rook(i, j);
						stones.push_back(rook);
					}
					else if (j == 1 || j == (boardLength - 2))
					{
						Stone* knight = new Knight(i, j);
						stones.push_back(knight);
					}
					else if (j == 2 || j == (boardLength - 3))
					{
						Stone* bishop = new Bishop(i, j);
						stones.push_back(bishop);
					}
					else if (j == 3)
					{
						Stone* queen = new Queen(i, j);
						stones.push_back(queen);
					}
					else if (j == 4)
					{
						Stone* king = new King(i, j);
						stones.push_back(king);
					}
				}
				catch (exception& ex) {
					cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
					exit(1); //no need to free anything
				}
			}
	}
}

void Player::addDamka(int boardLength, const Board& table) {
	if (_player == Players::PLAYER1) {
		for (int i = (boardLength - 3); i < boardLength; i++)
		{
			for (int j = 0; j < boardLength; j++)
			{
				try {
					if (i == (boardLength - 3) && !(j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
					else if (i == (boardLength - 2) && (j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
					else if (i == (boardLength - 1) && !(j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
				}
				catch (exception& ex) {
					cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
					exit(1); //no need to free anything
				}
			}
		}
	} //player 1
	else { //player 2
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < boardLength; j++)
			{
				try {
					if (i == 0 && (j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
					else if (i == 1 && !(j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
					else if (i == 2 && (j % 2))
					{
						Stone* pawn = new DamkaPawn(i, j);
						stones.push_back(pawn);
					}
				}
				catch (exception& ex) {
					cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
					exit(1); //no need to free anything
				}
			}
		}
	}
}

void Player::addAmazons(int boardLength, const Board& table) {
	if (_player == Players::PLAYER1)//initiallize stones for player 1 
	{
		try {
			Stone* first_amazon = new AmazonsStone((boardLength - 1), 3);
			stones.push_back(first_amazon);
			Stone* second_amazon = new AmazonsStone((boardLength - 1), 6);
			stones.push_back(second_amazon);
			Stone* third_amazon = new AmazonsStone(6, 0);
			stones.push_back(third_amazon);
			Stone* fourth_amazon = new AmazonsStone(6, (boardLength - 1));
			stones.push_back(fourth_amazon);
		}
		catch (exception& ex) {
			cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
			exit(1); //no need to free anything
		}
	}
	else //initiallize stones for player 2
	{
		try {
			Stone* first_amazon = new AmazonsStone(0, 3);
			stones.push_back(first_amazon);
			Stone* second_amazon = new AmazonsStone(0, 6);
			stones.push_back(second_amazon);
			Stone* third_amazon = new AmazonsStone(3, 0);
			stones.push_back(third_amazon);
			Stone* fourth_amazon = new AmazonsStone(3, (boardLength - 1));
			stones.push_back(fourth_amazon);
		}
		catch (exception& ex) {
			cout << "Allocation error: " << ex.what() << "\nThe program will now close." << endl;
			exit(1); //no need to free anything
		}
	}
}