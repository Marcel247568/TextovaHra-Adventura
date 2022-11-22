#include "GameLib.h"
#include "ANSI/ANSI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int COLUMNS;
static unsigned int ROWS;

void errorMessage(const char* message) {
	clearScreen();
	scrollMargins(1, ROWS);
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("\nERROR: ");
	setColor(FOREGROUND, DEFAULT_COLOR);
	printf_s("%s", message);
	exit(-1);
}

void quickMessage(const char* message) {
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("%s", message);
	setColor(FOREGROUND, BLACK);
	getchar();
	printInputBox();
}

void staticMessage(const char* message) {
	setColor(BRIGHT_FOREGROUND, WHITE);
	setColor(BACKGROUND, BLACK);
	deleteLine(7);
	absoluteCursorPosition(2, ROWS - 9);
	printf_s("%s", message);
}

void setup(const char* name, unsigned int columns, unsigned int rows) {
	COLUMNS = columns;
	ROWS = rows;
	if (setupConsole(columns, rows)) {
		errorMessage("chyba pri nastavovani konzole");
	}
	alternateBuffer(1);
	setWindowTitle(name);
	shapeCursor(BLOCK);
	scrollMargins(ROWS - 1, ROWS);
}

void close() {
	if (restoreConsole()) {
		errorMessage("chyba pri zavirani konzole");
	}
	scrollMargins(1, ROWS);
	exit(0);
}

void printMenu(unsigned int count, ...) {
	va_list choices;
	va_start(choices, count);
	const char* choice;
	for (unsigned int n = 0; n < count; n++) {
		absoluteCursorPosition((COLUMNS / 2) - 7, 3 * (ROWS / 5) + n);
		choice = va_arg(choices, const char*);
		printf("%u: ", n+1);
		printf_s("%s", choice);
	}
	va_end(choices);
	printInputBox();
}

void printInputBox() {
	absoluteCursorPosition(1, ROWS - 1);
	setColor(BRIGHT_BACKGROUND, WHITE);
	insertLine(1);
	setColor(BACKGROUND, BLACK);
	insertLine(1);
	setColor(BRIGHT_BACKGROUND, WHITE);
	setColor(FOREGROUND, BLACK);
	absoluteCursorPosition(2, ROWS);
	blinkCursor(1);
}

bool boolAnswer() {
	input:
	char answer[5];
	scanf_s("%s", answer, (unsigned int)sizeof(answer));
	while (getchar() != '\n');
	if (!strcmp(answer, "YES") || !strcmp(answer, "yes") || !strcmp(answer, "y") || !strcmp(answer, "Y") || !strcmp(answer, "1")) {
		printInputBox();
		return 1;
	}

	else if (!strcmp(answer, "NO") || !strcmp(answer, "no") || !strcmp(answer, "n") || !strcmp(answer, "N") || !strcmp(answer, "0")) {
		printInputBox();
		return 0;
	}

	else {
		printInputBox();
		quickMessage("Zadejte platny vstup");
		goto input;
	}
}

unsigned int numAnswer(unsigned int from, unsigned int to) {
	input:
	unsigned int answer;
	scanf_s("%u", &answer);
	while (getchar() != '\n');
	if (answer >= from && answer <= to) {
		printInputBox();
		return answer;
	}

	else {
		printInputBox();
		quickMessage("Zadejte platny vstup");
		goto input;
	}
}

void clearScreen() {
	setColor(BACKGROUND, BLACK);
	eraseViewport(ALL);
}

void printMap() {
	absoluteCursorPosition(COLUMNS / 5 + 1, 1);
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);

	char line[100];
	FILE* fmap;
	if (fopen_s(&fmap, "../../../data/map.dat", "r")) errorMessage("soubor map.dat se nepodarilo otevrit");
	
	while (!feof(fmap)) {
		fscanf_s(fmap, "#%[^\n]\n", line, sizeof(line));
		printf_s("%s\n", line);
		relativeCursorPosition(COLUMNS / 5 + 1, 0);
	}
	fclose(fmap);
}