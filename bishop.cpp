#include "bishop.h"
#include "player.h"

//ctor:
Bishop::Bishop(int x, int y) {
	pos.setPos(x, y);
}

//other:
void Bishop::findPossibleMoves(const Board& table, Player& player) {

	Position curr = pos;
	--curr;
	while (curr.isInTable(table))// diagonal left up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			--curr;
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

	curr.setPos(curr.getX() - 1, curr.getY() + 1);
	while (curr.isInTable(table))// diagonal right up
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setPos(curr.getX() - 1, curr.getY() + 1);
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

	++curr;
	while (curr.isInTable(table))// diagonal right down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			++curr;
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

	curr.setPos(curr.getX() + 1, curr.getY() - 1);
	while (curr.isInTable(table))// diagonal left down
	{
		if (table.getCellValue(curr) == SPACE)
		{
			possibleMoves.push_back(curr);
			curr.setPos(curr.getX() + 1, curr.getY() - 1);
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