#include "amazonsStone.h"

//ctor:
AmazonsStone::AmazonsStone(int x, int y) {
	pos.setPos(x, y);
}

//other:
void AmazonsStone::findPossibleMoves(const Board& table, Player& player)
{
	Position curr = pos;

	--curr;
	while (curr.isInTable(table))// diagonal left up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			--curr;
		}
		else
			break;
	}
	curr = pos;

	curr.setX(curr.getX() - 1); // Y stays the same
	while (curr.isInTable(table))// check up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() - 1);
		}
		else
			break;
	}
	curr = pos;

	curr.setX(curr.getX() - 1);
	curr.setY(curr.getY() + 1);
	while (curr.isInTable(table))// diagonal right up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() - 1);
			curr.setY(curr.getY() + 1);
		}
		else
			break;
	}
	curr = pos;

	curr.setY(curr.getY() + 1); // X stays the same
	while (curr.isInTable(table))// check right
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setY(curr.getY() + 1);
		}
		else
			break;
	}
	curr = pos;

	++curr;
	while (curr.isInTable(table))// diagonal right down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			++curr;
		}
		else
			break;
	}
	curr = pos;

	curr.setX(curr.getX() + 1); // Y stays the same
	while (curr.isInTable(table))// check down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() + 1);
		}
		else
			break;
	}
	curr = pos;

	curr.setX(curr.getX() + 1);
	curr.setY(curr.getY() - 1);
	while (curr.isInTable(table))// check diagonal left down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setX(curr.getX() + 1);
			curr.setY(curr.getY() - 1);
		}
		else
			break;
	}
	curr = pos;

	curr.setY(curr.getY() - 1);
	while (curr.isInTable(table))// check left
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setY(curr.getY() - 1);
		}
		else
			break;
	}
	curr = pos;
}
