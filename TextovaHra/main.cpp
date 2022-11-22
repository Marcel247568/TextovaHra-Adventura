// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameLib/GameLib.h"
#include "GameLib/ANSI/ANSI.h"

using namespace std;

int main()
{
	setup("GameName", 100, 30);

	struct playerData {
		char name[15];
	}player;
	
	clearScreen();
	printMenu(3, "Nova hra", "Nacist hru", "Konec");
	unsigned int choice;
	choice = numAnswer(1, 3);
	clearScreen();
	
	FILE* fplayer;
	switch (choice) {
		case 1:
			staticMessage("Zadejte jmeno sve postavy");
			printInputBox();
			scanf_s("%14s", &player.name, 15);
			printInputBox();
			
			if (fopen_s(&fplayer, "../../../data/player.dat", "wb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fwrite(&player, sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;

		case 2:
			if (fopen_s(&fplayer, "../../../data/player.dat", "rb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fread_s(&player, sizeof(struct playerData), sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;

		case 3:
			close();
			break;
	}

	clearScreen();
	printInputBox();
	printMap();
	

	while (1) {
		
	}

	close();
	getchar();
	return 0;
}