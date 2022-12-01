// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameLib/GameLib.h"
#include "GameLib/ANSI/ANSI.h"

using namespace std;

int main()
{
	const char* playerFile = "../../../data/player.dat";
	const char* mapFile = "../../../data/map.dat";
	const char* textFile = "../../../data/text.dat";
	const char* nameFile = "../../../data/name.dat";

	struct playerData {
		char name[15];
	}player;

	setup("GameName", 116, 30);
	
	clearScreen();

	printArtFile(nameFile, 1, 3);

	printMenu(43, 18, 3, "Nova hra", "Nacist hru", "Konec");
	unsigned int choice;
	choice = numAnswer(1, 3);
	clearScreen();
	
	FILE* fplayer;
	switch (choice) {
		case 1:
			staticMessage("Zadejte jmeno sve postavy");
			printInputBox();
			scanf_s("%14s", &player.name, 15);
			while (getchar() != '\n');
			printInputBox();
			
			if (fopen_s(&fplayer, playerFile, "wb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fwrite(&player, sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;

		case 2:
			if (fopen_s(&fplayer, playerFile, "rb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fread_s(&player, sizeof(struct playerData), sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;

		case 3:
			close();
			break;
	}

	clearScreen();
	printArtFile(mapFile, 20, 1);
	printInputBox();
	while (1) {
		
	}

	close();
	getchar();
	return 0;
}