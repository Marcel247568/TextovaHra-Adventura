// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "GameLib/GameLib.h"
#include "GameLib/ANSI/ANSI.h"
#include <stdbool.h>

using namespace std;

void pressEnter(unsigned int row);
void cryoRoom(struct playerData* player);

const char* textFile = "../../../data/text.dat";
struct playerData {
	char name[15];
	bool key;
};

int main()
{
	const char* mapFile = "../../../data/map.dat";
	const char* nameFile = "../../../data/name.dat";

	struct playerData player;

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
	
	switch (choice) {
		//zalozeni nove postavy
		case 1:
			printTextFile(textFile, 1, 1, 24);
			printInputBox();
			scanf_s("%14s", &player.name, 15);
			while (getchar() != '\n');
			printInputBox();
			player.key = 0;

			saveGame(&player, sizeof(struct playerData));
			break;

		//nasteni postavy
		case 2:
			loadGame(&player, sizeof(struct playerData));
			break;
		
		//ukonceni hry
		case 3:
			close();
			break;
	}

	if (choice == 1) {
		clearScreen();
		printTextFile(textFile, 2, 0, 2);
		printTextFile(textFile, 3, 0, 6);
		pressEnter(10);
	}
	
	clearScreen();
	printArtFile(mapFile, 20, 1);

	cryoRoom(&player);

	close();
	return 0;
}

void cryoRoom(struct playerData* player) {
	unsigned int choice, first, second, third;
	setColor(BRIGHT_FOREGROUND, WHITE);
	printTextFile(textFile, 5, 0, 20);
	pressEnter(24);

	start:
	printMenu(3, 20, 3, "Odejit", "Podivat se na stul", "Podivat se na skrinku");

	choice = numAnswer(1, 3);
	switch (choice) {
	case 1:
		if (player->key) {
			setColor(BACKGROUND, BLACK);
			setColor(BRIGHT_FOREGROUND, WHITE);

		}
		else {
			setColor(BACKGROUND, BLACK);
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 6, 0, 20);
			pressEnter(23);
			goto start;
		}
		break;

	case 2:
		setColor(BACKGROUND, BLACK);
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 7, 0, 20);
		pressEnter(22);
		goto start;
		break;

	case 3:
		setColor(BACKGROUND, BLACK);
		setColor(BRIGHT_FOREGROUND, WHITE);
		printTextFile(textFile, 8, 0, 20);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 9, 1, 22);
		printInputBox();
		first = numAnswer(1, 9);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 10, 1, 22);
		printInputBox();
		second = numAnswer(1, 9);
		setColor(FOREGROUND, WHITE);
		printTextFile(textFile, 11, 1, 22);
		printInputBox();
		third = numAnswer(1, 9);
		if (first == 8 && second == 5 && third == 7) {
			player->key = 1;
			saveGame(player, sizeof(struct playerData));
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 13, 0, 20);
			pressEnter(24);
			goto start;
		}
		else {
			setColor(BRIGHT_FOREGROUND, WHITE);
			printTextFile(textFile, 12, 1, 20);
			pressEnter(22);
			goto start;
		}
		break;
	}
}

void pressEnter(unsigned int row) {
	hideCursor(1);
	setColor(FOREGROUND, WHITE);
	printTextFile(textFile, 4, 1, row);
	while (getchar() != '\n');
	hideCursor(0);
}