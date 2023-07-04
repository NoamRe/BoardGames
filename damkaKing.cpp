#include "damkaKing.h"
#include "damkaBoard.h"

//ctor:
DamkaKing::DamkaKing(int x, int y) {
	pos.setPos(x, y);
}

//other:
void DamkaKing::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;

	if (table.getCellValue(curr) == DAMKA_WHITE_KING) //player1 = player with 'O'
	{
		//checking upper left:
		--curr; //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				--curr; //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				--curr; //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_BLACK ||
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting

		//checking upper right:
		curr.setPos(curr.getX() - 1, curr.getY() + 1); //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				curr.setPos(curr.getX() - 1, curr.getY() + 1); //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				curr.setPos(curr.getX() - 1, curr.getY() + 1); //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_BLACK ||
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting

		//checking lower right:
		++curr; //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				++curr; //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				++curr; //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_BLACK ||
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting


		//checking lower left:
		curr.setPos(curr.getX() + 1, curr.getY() - 1); //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				curr.setPos(curr.getX() + 1, curr.getY() - 1); //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				curr.setPos(curr.getX() + 1, curr.getY() - 1); //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_BLACK ||
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting
	} //player 1
	else //player 2
	{
		//checking upper left:
		--curr; //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				--curr; //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				--curr; //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_WHITE ||
						table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting

		//checking upper right:
		curr.setPos(curr.getX() - 1, curr.getY() + 1); //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				curr.setPos(curr.getX() - 1, curr.getY() + 1); //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				curr.setPos(curr.getX() - 1, curr.getY() + 1); //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_WHITE ||
						table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting

		//checking lower right:
		++curr; //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				++curr; //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				++curr; //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_WHITE ||
						table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting


		//checking lower left:
		curr.setPos(curr.getX() + 1, curr.getY() - 1); //moving one
		while (curr.isInTable(table))
		{
			if (table.getCellValue(curr) == SPACE)
			{
				possibleMoves.push_back(curr);
				curr.setPos(curr.getX() + 1, curr.getY() - 1); //move anoter one
			}
			else { //there isnt a space
				Position oldPos = curr;
				curr.setPos(curr.getX() + 1, curr.getY() - 1); //moving another one
				if (curr.isInTable(table) && //checking if its in table
					(table.getCellValue(oldPos) == DAMKA_WHITE ||
						table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
					break; //cant move anymore
				}
				else
					break; //cant move anymore
			}
		}
		curr = pos; //resetting
	} //player 2
}