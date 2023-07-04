#include "king.h"
#include "knight.h"
#include "player.h"

//ctor:
King::King(int x, int y) {
	pos.setPos(x, y);
}

//other:
bool King::isCheckmate(const Board& table, Player& currPlayer, Player& otherPlayer) {
	if (possibleMoves.size() == 0) {
		char currC = table.getCellValue(pos);
		int amountOfRisks = pos.getRisksSize(table, currC);
		if (amountOfRisks == 0)
			return false; //no checkmate, no risks
		else if (amountOfRisks > 1)
			return true; //checkmate, cant move anywhere and multiple risks
		else { //risks==1
			Stone& risk = otherPlayer.getStoneByPos(pos.getRisk(otherPlayer));
			Position riskPos = risk.getPos();
			if (riskPos.getRisksSize(currPlayer) > 0) //the current player can eat him
				return false;
			else if (typeid(risk) == typeid(Knight)) { //if the only risk is a knight and cant be eaten  
				return true;
			} //knight
			else { //bishop, queen or rook
				while (!(riskPos == pos)) { //check if you can block the path
					if (riskPos.getX() < pos.getX()) { //above the king
						if (riskPos.getY() < pos.getY()) //left of the king
						{
							++riskPos;

						}
						else if (riskPos.getY() > pos.getY()) { //right
							riskPos.setPos(riskPos.getX() + 1, riskPos.getY() - 1);

						}
						else //same column
						{
							riskPos.setX(riskPos.getX() + 1);

						}
					}
					else if (riskPos.getX() > pos.getX()) { //below the king
						if (riskPos.getY() < pos.getY()) //left of the king
						{
							riskPos.setPos(riskPos.getX() - 1, riskPos.getY() + 1);

						}
						else if (riskPos.getY() > pos.getY()) { //right
							--riskPos;

						}
						else //same column
						{
							riskPos.setX(riskPos.getX() - 1);

						}
					}
					else { //same row
						if (riskPos.getY() < pos.getY()) //left of the king
						{
							riskPos.setY(riskPos.getY() + 1);

						}
						else { //if (riskPos.getY() > pos.getY()) 
							riskPos.setY(riskPos.getY() - 1);

						}
					}
					//checking if the position can be blocked
					if (currPlayer.isPosInPossibleMovesOfAnyStone(riskPos))
						return false;
				} //while
				return true;
			}
		}
	}
	else
		return false;
}
void King::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;
	char currC = table.getCellValue(pos);
	--curr;
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setX(curr.getX() - 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setPos(curr.getX() - 1, curr.getY() + 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setY(curr.getY() + 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	++curr;
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setX(curr.getX() + 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setPos(curr.getX() + 1, curr.getY() - 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;

	curr.setY(curr.getY() - 1);
	if (curr.isInTable(table)) {
		if (table.getCellValue(curr) == SPACE) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
		else if (player.isStoneInListByPos(curr)) {
			if (curr.getRisksSize(table, currC) == 0) {
				possibleMoves.push_back(curr);
			}
		}
	}
	curr = pos;
}

