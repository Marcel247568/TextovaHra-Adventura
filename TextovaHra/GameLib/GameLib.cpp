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
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("\nERROR: ");
	setColor(FOREGROUND, WHITE);
	printf_s("%s", message);
	exit(-1);
}

void quickMessage(const char* message) {
	setColor(BRIGHT_BACKGROUND, WHITE);
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("%s", message);
	setColor(FOREGROUND, BLACK);
	getchar();
	printInputBox();
}

void staticMessage(const char* message) {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
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

void printMenu(unsigned int column, unsigned int row, unsigned int count, ...) {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	va_list choices;
	va_start(choices, count);
	const char* choice;
	for (unsigned int n = 0; n < count; n++) {
		absoluteCursorPosition(column, row + n);
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

void printArtFile(const char* file, unsigned int column, unsigned int row) {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	absoluteCursorPosition(column, row);

	char* line;
	line = (char*)malloc(255 * sizeof(char));
	FILE* fG;
	if (fopen_s(&fG, file, "r")) errorMessage("soubor s grafickym obsahem se nepodarilo otevrit");
	while (!feof(fG)) {
		fscanf_s(fG, "#%[^\n]\n", line, (unsigned int)(255 * sizeof(char)));
		printf_s("%s\n", line);
		absoluteCursorPosition(column, 0);
	}
	fclose(fG);
	free(line);
}

void printTextFile(const char* file, unsigned int column, unsigned int row) {
	setColor(BACKGROUND, BLACK);
	setColor(BRIGHT_FOREGROUND, WHITE);
	absoluteCursorPosition(column, row);

	char* text;
	text = (char*)malloc(255 * sizeof(char));
	FILE* fT;
	if (fopen_s(&fT, file, "r")) errorMessage("soubor s textovym obsahem se nepodarilo otevrit");
	while (!feof(fT)) {
		fscanf_s(fT, "%[^\n]\n", text, (unsigned int)(255 * sizeof(char)));
		printf_s("%s\n", text);
		absoluteCursorPosition(column, 0);
	}
	fclose(fT);
	free(text);
}