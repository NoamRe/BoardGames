#pragma once

#include "game.h"

class Menu {
public:
	//ctor:
	Menu();

	//dtor:
	~Menu();

	//getters:
	bool programRunning() const;//while user doesn't enter 8

	//setters:
	void setChoice();//set choice by user input
	void setProgramFinish();//to execute program

	//other:
	void printMenu() const;//print menu each time for user's choice
	void exitProgram();//finish program

	//load from file:
	void loadToCurrGame();

private:
	list<Game*> games;
	int choice;		  //user's choice
	bool isRunning;   
	list<Game*>::iterator currGame;//iterator Game*
};