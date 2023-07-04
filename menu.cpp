#include "menu.h"
#include "chessGame.h"
#include "damkaGame.h"
#include "amazonsGame.h"


//ctor:
Menu::Menu() : choice(-1), isRunning(true) {};

//dtor:
Menu::~Menu() {
	//deleting all the games:
	for (auto itr = games.begin(); itr != games.end(); ++itr)
		delete (*itr);
}

//getters:
bool Menu::programRunning() const {
	return isRunning;
}

//setters:
void Menu::setChoice() {
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "\nPlease choose the type of the game to add:\n1) Damka\n2) Amazons\n3) Chess\n";
		cin >> choice;
		switch (choice) {
		case 1: {
			Game* damka = new DamkaGame;
			games.push_back(damka);
			currGame = games.end();
			--currGame;
			break;
		}
		case 2: {
			Game* amazons = new AmazonsGame;
			games.push_back(amazons);
			currGame = games.end();
			--currGame;
			break;
		}
		case 3: {
			Game* chess = new ChessGame;
			games.push_back(chess);
			currGame = games.end();
			--currGame;
			break;
		}
		default: {  string error = "You have entered the wrong number!\n";
			throw invalid_argument(error);
		}
		}
		cout << "\nA new game was added!" << endl;
		break;
	case 2: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else
	{
		if (currGame == (--games.end()) && currGame == games.begin())//only one game in list
		{
			string error = "There is only one game in progress!\n\n";
			throw logic_error(error);
		}
		else if (currGame == (--games.end()))//currgame is pointing to last game
		{
			currGame = games.begin();
			cout << "The current game has advanced and the game is the first one!" << endl;
		}
		else
		{
			++currGame;
			cout << "The current game has advanced!" << endl;
		}
	}
		  break;
	case 3: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else
	{
		delete(*currGame);
		currGame = games.erase(currGame);
		if (currGame == games.end())
			currGame = games.begin();

		cout << "The current game has been removed!" << endl;
	}

		  break;
	case 4: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else (*currGame)->print();
		break;
	case 5: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else if ((*currGame)->getIsFinished()) {
		string error = "The game has ended!\n";
		throw logic_error(error);
	}
		  else
	{
		cout << "Please enter coordinates of a stone:" << endl;
		Position pos;
		cin >> pos;

		if (!pos.isInTable((*currGame)->getBoard()))// stone is out of boudaries
		{
			string error = "The coordinate " + static_cast<string>(pos) +" are out of the game board!\n";
			throw out_of_range(error);
		}
		else if ((*currGame)->getCurrPlayer().isStoneInListByPos(pos))
			(*currGame)->getCurrPlayer().getStoneByPos(pos).printPossibleMoves();
		else if ((*currGame)->getOtherPlayer().isStoneInListByPos(pos))
			(*currGame)->getOtherPlayer().getStoneByPos(pos).printPossibleMoves();
		else {
			string error = "There is no stone in coordinate " + static_cast<string>(pos);
			throw invalid_argument(error);
		}
	}
		  break;
	case 6: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else if ((*currGame)->getIsFinished()) {
		string error = "The game has ended!\n";
		throw logic_error(error);
	}
		  else { //risks
		cout << "Please enter coordinates of a position:" << endl;

		Position pos;
		cin >> pos;

		if (!pos.isInTable((*currGame)->getBoard())) {
			string error = "The coordinate " + static_cast<string>(pos) +" are out of the game board!\n";
			throw out_of_range(error);
		}
		else if (typeid(*(*currGame)) == typeid(ChessGame) || typeid(*(*currGame)) == typeid(DamkaGame)) {
			if ((*currGame)->getCurrPlayer().isStoneInListByPos(pos))
				pos.printRisks<Player>((*currGame)->getOtherPlayer());
			else if ((*currGame)->getOtherPlayer().isStoneInListByPos(pos))
				pos.printRisks<Player>((*currGame)->getCurrPlayer());
			else {
				string error = "There is no stone in coordinate " + static_cast<string>(pos);
				throw invalid_argument(error);
			}
		}
		else if (typeid(*(*currGame)) == typeid(AmazonsGame))
		{
			if ((*currGame)->getBoard().getCellValue(pos) == SPACE)
				pos.printRisks<Board>((*currGame)->getBoard());
			else
			{
				string error = "There is no space in coordinate " + static_cast<string>(pos);
				throw invalid_argument(error);
			}
		}
	}
		  break;
	case 7: if (games.empty()) {
		string error = "There are no available games!\n";
		throw logic_error(error);
	}
		  else if ((*currGame)->getIsFinished()) {
		string error = "The game has ended!\n";
		throw logic_error(error);
	}
		  else
	{
		cout << "Please enter coordinates to move from:" << endl;

		Position moveFrom;
		cin >> moveFrom;

		cout << "Please enter coordinates to move to:" << endl;
		Position moveTo;
		cin >> moveTo;

		(*currGame)->makeMove(moveFrom, moveTo);
	}
		  break;
	case 8: exitProgram();//update all new[] games 
		break;

	case 9: if (games.empty()) {
		string error = "There are no available games to save!\n";
		throw logic_error(error);
	}
		  (*currGame)->saveCurrGame();
		  break;

	case 10:
		loadToCurrGame();
		//loadFromFile(), will throw exception
		break;
	default: string error = "You have entered the wrong number!\n";
		throw invalid_argument(error);
	}
}
void Menu::setProgramFinish() { isRunning = false; }

//other:
void Menu::exitProgram() {
	cout << "The program will now quit...goodbye!" << endl;
	setProgramFinish();
}

void Menu::printMenu() const
{
	cout << "Please choose one of the following options:\n\n";
	cout << "(Please note, coordinates are entered row first and column second)\n\n";
	cout << "1) Add a new game!\n";//add new item to list
	cout << "2) Continue to the next game on the list.\n";//advance curr game
	cout << "3) Delete the current game.\n";//delete item in list
	cout << "4) Print the current game's table.\n"; //print game table + game status + player's turn + if someone won
	cout << "5) Print the possible moves of a wanted game stone.\n";//all coordinate that stone can move to
	cout << "6) Print the possible risks of a wanted position.\n";//all the coordinates that can be moved from to the wanted of user
	cout << "7) Make a move!\n";//insert stone, legal coordinate and legal wall and update board
	cout << "8) Exit the program!\n"; // delete all games and status in every game
	cout << "9) Save game to file!\n"; //saves game to a file
	cout << "10) Load game from file!\n\n"; //loads a game from a file
}

//load from file:
void Menu::loadToCurrGame()
{
	string fileName;
	cout << "Enter file name to load from: ";

	cin >> fileName;
	ifstream inFile(fileName.c_str(), ios::binary);
	if (!inFile.is_open())
	{
		string error = "couldnt find file\n";
		throw logic_error(error);
	}
	cout << "loading from file...\n\n";
	GameType type;

	inFile.read(rcastc(&type), sizeof(GameType));
	Game* g = nullptr;
	if (type == GameType::ChessGame)
	{
		try {
			g = new ChessGame(inFile);
		}
		catch (bad_alloc& ex) {
			cout << "Allocation Error: " << ex.what();
			exit(1);
		}
	}
	else if (type == GameType::DamkaGame)
	{
		try {
			g = new DamkaGame(inFile);
		}
		catch (bad_alloc& ex) {
			cout << "Allocation Error: " << ex.what();
			exit(1);
		}
	}
	else if (type == GameType::AmazonsGame)
	{
		try {
			g = new AmazonsGame(inFile);
		}
		catch (bad_alloc& ex) {
			cout << "Allocation Error: " << ex.what();
			exit(1);
		}
	}

	g->getCurrPlayer().initStonesInList(g->getBoard(), g->getOtherPlayer());//initiallize posible move 
	g->getOtherPlayer().initStonesInList(g->getBoard(), g->getCurrPlayer());//initiallize posible move


	games.push_back(g);
	currGame = (--games.end());
	cout << "Game loaded succcefully!\n\n";
	
}
