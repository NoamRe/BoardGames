#include "knight.h"
#include "player.h"

//ctor:
Knight::Knight(int x, int y) {
	pos.setPos(x, y);
}

//other:
void Knight::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;

	curr.setPos(curr.getX() + 2, curr.getY() + 1);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() + 2, curr.getY() - 1);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() - 2, curr.getY() - 1);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() - 2, curr.getY() + 1);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() + 1, curr.getY() + 2);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() + 1, curr.getY() - 2);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() - 1, curr.getY() + 2);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;

	curr.setPos(curr.getX() - 1, curr.getY() - 2);
	if (curr.isInTable(table))
	{
		if (table.getCellValue(curr) == SPACE) {
			possibleMoves.push_back(curr);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
		}
	}
	curr = pos;
}