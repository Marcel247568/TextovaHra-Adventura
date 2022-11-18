// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameName.h"
#include "ANSI.h"

using namespace std;

int main()
{
	setup("GameName", 90, 30);

	printMenu(4, "Nova hra", "Nacist hru", "Nastaveni", "Konec");
	unsigned int choice;
	scanf_s("%u", &choice);
	
	switch (choice) {
		case 1:
			//zde bude funkce pro novou hru
			break;
		case 2:
			//zde bude funkce pro nacteni hry
			break;
		case 3:
			//zde bude funkce pro nastaveni
			break;
		case 4:
			//zde bude funkce pro ukonceni hry
			break;
		default:
			//zde bude funkce rychlou zprávu v textovém poli
			;

	}

	if (restoreConsole()) {
		errorMessage("chyba pri zavirani konzole");
		return -1;
	}

	getchar();
	return 0;
}