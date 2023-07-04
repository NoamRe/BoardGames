#include "rook.h"
#include "player.h"

//ctor:
Rook::Rook(int x, int y) {
	pos.setPos(x, y);
}

//other:
void Rook::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;

	curr.setX(curr.getX() - 1);
	while (curr.isInTable(table))// up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() - 1);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
			break;
		}
		else
			break;
	}
	curr = pos;

	curr.setY(curr.getY() + 1);
	while (curr.isInTable(table))// right
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setY(curr.getY() + 1);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
			break;
		}
		else
			break;
	}
	curr = pos;

	curr.setX(curr.getX() + 1);
	while (curr.isInTable(table))// down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() + 1);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
			break;
		}
		else
			break;
	}
	curr = pos;

	curr.setY(curr.getY() - 1);
	while (curr.isInTable(table))// left
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setY(curr.getY() - 1);
		}
		else if (player.isStoneInListByPos(curr))
		{
			possibleMoves.push_back(curr);
			break;
		}
		else
			break;
	}
	curr = pos;
}
