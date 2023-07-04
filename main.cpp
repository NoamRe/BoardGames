#include "menu.h"

int main() 
{
	Menu m;
	while (m.programRunning()) {
		m.printMenu();
		try {
			m.setChoice();
		}
		catch (exception& ex) {
			cout << "\nThere was an error: " << ex.what() << endl;
		}
	}
}