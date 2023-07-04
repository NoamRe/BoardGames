#include "damkaPawn.h"
#include "damkaBoard.h"

//ctor:
DamkaPawn::DamkaPawn(int x, int y) {
	pos.setPos(x, y);
}
//setters:
void DamkaPawn::setKing(Board& table) {
	(table.getCellValue(pos) == DAMKA_BLACK) ? (table.setCellValue(DAMKA_BLACK_KING, pos)) :
		(table.setCellValue(DAMKA_WHITE_KING, pos));
}

//other:
void DamkaPawn::findPossibleMoves(const Board& table, Player& player) {
	Position curr = pos;

	if (table.getCellValue(curr) == DAMKA_WHITE) //player1 = player with 'o'
	{
		//upper right:
		curr.setPos(curr.getX() - 1, curr.getY() + 1); //move to upper right
		if (curr.isInTable(table)) { //check if that pos is in table
			if (table.getCellValue(curr) == SPACE) { //if its a space, its good
				possibleMoves.push_back(curr);
			}
			else { //not a space
				Position oldPos = curr; //save the previous position and move one more
				curr.setPos(curr.getX() - 1, curr.getY() + 1); //move one more
				if (curr.isInTable(table) && //check if its in table
					(table.getCellValue(oldPos) == DAMKA_BLACK || //check if the old one is an enemy
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) { //and if the pos is a space 
					possibleMoves.push_back(curr);
				}
			}
		} //upper right
		curr = pos; //reset pos

		//upper left:
		--curr; //move to upper left
		if (curr.isInTable(table)) { //check if that pos is in table
			if (table.getCellValue(curr) == SPACE) { //if its a space its good
				possibleMoves.push_back(curr);
			}
			else { //not a space
				Position oldPos = curr; //save the previous position and move one more
				--curr;
				if (curr.isInTable(table) && //check if it's in table
					(table.getCellValue(oldPos) == DAMKA_BLACK ||
						table.getCellValue(oldPos) == DAMKA_BLACK_KING) &&
					table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
				}
			}
		} //upper left
		curr = pos; //reset pos
	} //player 1 
	else //player2
	{
		if (curr.isInTable(table)) // first check if stone is in table boundaries
		{
			//lower right:
			++curr; //move one
			if (curr.isInTable(table)) {
				if (table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
				}
				else { //not a space
					Position oldPos = curr; //save the previous position and move one more
					++curr; //move another time
					if (curr.isInTable(table) && //check if its in table
						(table.getCellValue(oldPos) == DAMKA_WHITE ||
							table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
						table.getCellValue(curr) == SPACE) {
						possibleMoves.push_back(curr);
					}
				}
			}//lower right
			curr = pos; //reset pos

			//lower left:
			curr.setPos(curr.getX() + 1, curr.getY() - 1); //move one
			if (curr.isInTable(table)) { // first check if stone is in table boundaries
				if (table.getCellValue(curr) == SPACE) {
					possibleMoves.push_back(curr);
				}
				else {
					Position oldPos = curr; //save the previous position and move one more
					curr.setPos(curr.getX() + 1, curr.getY() - 1); //move another one
					if (curr.isInTable(table) && //check if its in table
						(table.getCellValue(oldPos) == DAMKA_WHITE ||
							table.getCellValue(oldPos) == DAMKA_WHITE_KING) &&
						table.getCellValue(curr) == SPACE) {
						possibleMoves.push_back(curr);
					}
				}
			} //lower left
			curr = pos;
		}// if in table
	} //player 2
}
