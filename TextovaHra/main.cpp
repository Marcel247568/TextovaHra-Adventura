// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameName.h"
#include "ANSI.h"

using namespace std;

int main()
{
	setup("GameName", 80, 30);
	printIntro();
	printMenu(4, "Nova hra", "Nacist hru", "Nastaveni", "Konec");

	//switch na menu

	if (restoreConsole()) {
		errorMessage("chyba pri zavirani konzole");
		return -1;
	}

	getchar();
	return 0;
}