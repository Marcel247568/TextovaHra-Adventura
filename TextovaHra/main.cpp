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
		char cosi[13];
		char name[15];
	}player;
	
	clearScreen();
	printMenu(3, "Nova hra", "Nacist hru", "Konec");
	unsigned int choice;
	printInputBox();
	choice = numAnswer(1, 3);
	clearScreen();
	
	FILE* fplayer;
	switch (choice) {
		case 1:
			staticMessage("Zadejte jmeno sve postavy:");
			scanf_s("%14s", &player.name, 15);
			if (fopen_s(&fplayer, "C:\\MyFiles\\School\\BPC-PC1T\\SemestralProject\\TextovaHra\\player.dat", "ab")) {
				errorMessage("soubor player.dat se nepodarilo otevrit");
				exit(-1);
			}
			fwrite(&player, sizeof(struct playerData), 1, fplayer);
			fclose(fplayer);
			break;
		case 2:
			if (fopen_s(&fplayer, "C:\\MyFiles\\School\\BPC-PC1T\\SemestralProject\\TextovaHra\\player.dat", "rb")) {
				errorMessage("soubor player.dat se nepodarilo otevrit");
				exit(-1);
			}
			fread_s(&player, sizeof(struct playerData), sizeof(struct playerData), 1, fplayer);
			break;
		case 3:
			close();
			break;
	}

	while (1) {

	}

	close();
	getchar();
	return 0;
}