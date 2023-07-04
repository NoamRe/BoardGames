#include "position.h"
#include "chessBoard.h"
#include "stone.h"
#include "player.h"
#include <istream>

//ctor:
Position::Position(int x, int y) : _x(x), _y(y) {};
Position::Position() : _x(-1), _y(-1) {};

//copy ctor:
Position::Position(const Position& other) {
	*this = other;
}

//move ctor:
Position::Position(Position&& other) noexcept {
	_x = other._x;
	_y = other._y;
	risks = other.risks;
}

//getters:
int Position::getY() const { return _y; }
int Position::getX() const { return _x; }
Position& Position::getRisk(Player& player) {
	findPossibleRisks(player);
	return risks.at(0);
}

int Position::getRisksSize(const Board& table, char cellValue) {
	findPossibleRisks(table, cellValue);
	risks.clear();
	return risks.size();
}

int Position::getRisksSize(Player& otherPlayer) {
	findPossibleRisks(otherPlayer);
	risks.clear();
	return risks.size();
}

//setters:

void Position::setX(const int x) { _x = x; }
void Position::setY(const int y) { _y = y; }
void Position::setPos(const int x, const int y)
{
	_x = x;
	_y = y;
}

//operators:
const Position& Position::operator++()
{
	++_x;
	++_y;
	return *this;
}
const Position& Position::operator--()
{
	--_x;
	--_y;
	return *this;
}
bool Position::operator==(const Position& other) const
{
	return (other.getX() == _x && other.getY() == _y);
}
void Position::operator=(const Position& other) {
	if (this != &other)
	{
		_x = other.getX();
		_y = other.getY();
	}
}
istream& operator>>(istream& is, Position& pos)
{
	int curX, curY;
	is >> curX >> curY;
	pos.setPos(curX - 1, curY - 1);
	return is;
}
ostream& operator<<(ostream& os, const Position& pos)
{
	os << "(" << pos.getX() + 1 << "," << pos.getY() + 1 << ")";
	return os;
}
Position::operator string() const
{
	string s = "(" + to_string(getX() + 1) + ", " + to_string(getY() + 1) + ")";
	return s;
}

//other:
const bool Position::isInTable(const Board& table) const
{
	return (_x >= 0 && _y >= 0 && _x < table.getLength() && _y < table.getLength());
}

void Position::findPossibleRisks(const Board& table, char cellValue) {
	Players player;
	if (cellValue == CHESS_BLACK_BISHOP || cellValue == CHESS_BLACK_KING || cellValue == CHESS_BLACK_KNIGHT ||
		cellValue == CHESS_BLACK_PAWN || cellValue == CHESS_BLACK_QUEEN || cellValue == CHESS_BLACK_ROOK)
		player = Players::PLAYER2;
	else player = Players::PLAYER1;
	Position curr = *this;
	--curr;
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING || cellValue == CHESS_BLACK_PAWN) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			--curr;
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_BISHOP
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_BISHOP
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setX(curr.getX() - 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setX(curr.getX() - 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_ROOK
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_ROOK
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setPos(curr.getX() - 1, curr.getY() + 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING || cellValue == CHESS_BLACK_PAWN) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setPos(curr.getX() - 1, curr.getY() + 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_BISHOP
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_BISHOP
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setY(curr.getY() + 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setY(curr.getY() + 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_ROOK
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_ROOK
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	++curr;
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING || cellValue == CHESS_WHITE_PAWN) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			++curr;
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_BISHOP
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_BISHOP
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setX(curr.getX() + 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setX(curr.getX() + 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_ROOK
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_ROOK
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setPos(curr.getX() + 1, curr.getY() - 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING || cellValue == CHESS_WHITE_PAWN) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setPos(curr.getX() + 1, curr.getY() - 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_BISHOP
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_BISHOP
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setY(curr.getY() - 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
		else { //player 2
			if (cellValue == CHESS_WHITE_KING) {
				risks.push_back(curr);
				curr.setPos(-1, -1);
			}
		}
	}
	while (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue == SPACE)
			curr.setY(curr.getY() - 1);
		else if (player == Players::PLAYER1) {
			if (cellValue == CHESS_BLACK_ROOK
				|| cellValue == CHESS_BLACK_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
		else {//player 2
			if (cellValue == CHESS_WHITE_ROOK
				|| cellValue == CHESS_WHITE_QUEEN)
			{
				risks.push_back(curr);
				break;
			}
			else break;
		}
	}
	curr = *this;

	curr.setPos(curr.getX() - 2, curr.getY() - 1);
	if (curr.isInTable(table)) {
		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
				{
					risks.push_back(curr);
				}
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
				{
					risks.push_back(curr);
				}
		}
	}
	curr = *this;

	curr.setPos(curr.getX() - 2, curr.getY() + 1);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() - 1, curr.getY() + 2);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() + 1, curr.getY() + 2);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() + 2, curr.getY() + 1);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() + 2, curr.getY() - 1);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() + 1, curr.getY() - 2);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;

	curr.setPos(curr.getX() - 1, curr.getY() - 2);
	if (curr.isInTable(table)) {

		cellValue = table.getCellValue(curr);
		if (cellValue != SPACE) {
			if (player == Players::PLAYER1) {
				if (cellValue == CHESS_BLACK_KNIGHT)
					risks.push_back(curr);
			}
			else //player 2
				if (cellValue == CHESS_WHITE_KNIGHT)
					risks.push_back(curr);
		}
	}
	curr = *this;
}

void Position::findPossibleRisks(Player& player)
{
	risks = player.findRisksInList(*this);
}

void Position::findPossibleRisks(const Board& table)
{
	Position curr = *this;

	--curr;
	while (curr.isInTable(table))// diagonal left up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			--curr;
		}
		else
			break;
	}
	curr = *this;

	curr.setX(curr.getX() - 1); // Y stays the same
	while (curr.isInTable(table))// check up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setX(curr.getX() - 1);
		}
		else
			break;
	}
	curr = *this;

	curr.setPos(curr.getX() - 1, curr.getY() + 1);
	while (curr.isInTable(table))// diagonal right up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setPos(curr.getX() - 1, curr.getY() + 1);
		}
		else
			break;
	}
	curr = *this;

	curr.setY(curr.getY() + 1);// X stays the same
	while (curr.isInTable(table))// check right
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setY(curr.getY() + 1);
		}
		else
			break;
	}
	curr = *this;

	++curr;
	while (curr.isInTable(table))// diagonal right down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			++curr;
		}
		else
			break;
	}
	curr = *this;


	curr.setX(curr.getX() + 1); // Y stays the same
	while (curr.isInTable(table))// check down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setX(curr.getX() + 1);
		}
		else
			break;
	}
	curr = *this;


	curr.setPos(curr.getX() + 1, curr.getY() - 1);
	while (curr.isInTable(table))// check diagonal left down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setPos(curr.getX() + 1, curr.getY() - 1);
		}
		else
			break;
	}
	curr = *this;

	curr.setY(curr.getY() - 1);
	while (curr.isInTable(table))// check left
	{
		if (table.getCellValue(curr) == SPACE)
		{
			risks.push_back(curr);
			curr.setY(curr.getY() - 1);
		}
		else
			break;
	}
	curr = *this;
}

bool Position::findPosInRisks(const Board& table, const Position& wallPosition)
{
	findPossibleRisks(table);
	int size = static_cast<int>(risks.size());
	for (int i = 0; i < size; i++)
	{
		if (risks.at(i) == wallPosition)
		{
			risks.clear();
			return true;
		}
	}
	risks.clear();
	return false;
}

//load and save:
void Position::savePosition(ostream& outFile) const
{
	outFile.write(rcastcc(&_x), sizeof(int));
	outFile.write(rcastcc(&_y), sizeof(int));

}

void Position::loadPosition(istream& inFile)
{
	inFile.read(rcastc(&_x), sizeof(int));
	inFile.read(rcastc(&_y), sizeof(int));
}
