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

	setup("Destination Unknown", 100, 30);
	clearScreen();

	printArtFile(nameFile, 8, 3);
	printMenu(43, 20, 3, "Nova hra", "Nacist hru", "Konec");
	unsigned int choice;
	choice = numAnswer(1, 3);
	absoluteCursorPosition(43, 20);
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	eraseViewport(CURSOR_TO_END);
	
	FILE* fplayer;
	switch (choice) {
		//zalozeni nove postavy
		case 1:
			printTextFile(textFile, 1, 1, 24);
			printInputBox();
			scanf_s("%14s", &player.name, 15);
			while (getchar() != '\n');
			printInputBox();
			
			if (fopen_s(&fplayer, playerFile, "wb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fwrite(&player, sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;

		//nasteni postavy
		case 2:
			if (fopen_s(&fplayer, playerFile, "rb")) errorMessage("soubor player.dat se nepodarilo otevrit");
			fread_s(&player, sizeof(struct playerData), sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;
		
		//ukonceni hry
		case 3:
			close();
			break;
	}

	clearScreen();
	printTextFile(textFile, 2, 0, 2);
	printTextFile(textFile, 3, 0, 6);
	hideCursor(1);
	setColor(FOREGROUND, WHITE);
	printTextFile(textFile, 4, 1, 10);
	getchar();
	while (getchar() != '\n');
	hideCursor(0);

	clearScreen();
	printArtFile(mapFile, 20, 1);
	printInputBox();

	while (1) {
		
	}

	close();
	return 0;
}