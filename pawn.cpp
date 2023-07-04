#include "pawn.h"
#include "chessBoard.h"
#include "player.h"

//ctor:
Pawn::Pawn(int x, int y) {
	pos.setPos(x, y);
}

//setters:
void Pawn::setQueen(Board& table) {
	(table.getCellValue(pos) == CHESS_BLACK_PAWN) ?
		table.setCellValue(CHESS_BLACK_QUEEN, pos) : table.setCellValue(CHESS_WHITE_QUEEN, pos);
}

//other:
void Pawn::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;
	if (curr.isInTable(table)) {
		char value = table.getCellValue(curr);
		switch (value) {
		case (CHESS_BLACK_PAWN):
			if (curr.getX() == 1) { //starting line, can move 2
				curr.setX(curr.getX() + 2);
				if (table.getCellValue(curr) == SPACE)
				{
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setX(curr.getX() + 1);
			if (curr.isInTable(table)) {
				if (table.getCellValue(curr) == SPACE)
				{
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setPos(curr.getX() + 1, curr.getY() + 1);
			if (curr.isInTable(table)) {
				if (player.isStoneInListByPos(curr)) {
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setPos(curr.getX() + 1, curr.getY() - 1);
			if (curr.isInTable(table)) {
				if (player.isStoneInListByPos(curr)) {
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			break;
		case (CHESS_WHITE_PAWN):
			if (curr.getX() == (table.getLength() - 2)) { //starting line, can move 2
				curr.setX(curr.getX() - 2);
				if (table.getCellValue(curr) == SPACE)
				{
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setX(curr.getX() - 1);
			if (curr.isInTable(table)) {
				if (table.getCellValue(curr) == SPACE)
				{
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setPos(curr.getX() - 1, curr.getY() + 1);
			if (curr.isInTable(table)) {
				if (player.isStoneInListByPos(curr)) {
					possibleMoves.push_back(curr);
				}
			}
			curr = pos;

			curr.setPos(curr.getX() - 1, curr.getY() - 1);
			if (curr.isInTable(table)) {
				if (player.isStoneInListByPos(curr)) {
					possibleMoves.push_back(curr);
				}
			}
			curr = curr;

			break;
		}
	}
}