#include "GameLib.h"
#include "ANSI/ANSI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int COLUMNS;
static unsigned int ROWS;

void errorMessage(const char* message) {
	setStyle(1, DEFAULT_STYLE);
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("\nERROR: ");
	setColor(FOREGROUND, DEFAULT_COLOR);
	for (int c = 0; message[c] != '\0'; c++) printf_s("%c", message[c]);
}

void quickMessage(const char* message) {
	setColor(BRIGHT_FOREGROUND, RED);
	for (int c = 0; message[c] != '\0'; c++) printf_s("%c", message[c]);
	setColor(FOREGROUND, BLACK);
	getchar();
	printInputBox();
}

void staticMessage(const char* message) {
	setColor(BRIGHT_FOREGROUND, WHITE);
	setColor(BACKGROUND, BLACK);
	absoluteCursorPosition(2, ROWS - 9);
	for (int c = 0; message[c] != '\0'; c++) printf_s("%c", message[c]);
}

void setup(const char* name, unsigned int columns, unsigned int rows) {
	COLUMNS = columns;
	ROWS = rows;
	if (setupConsole(columns, rows)) {
		errorMessage("chyba pri nastavovani konzole");
		exit(-1);
	}
	alternateBuffer(1);
	setWindowTitle(name);
	shapeCursor(BLOCK);
	scrollMargins(ROWS - 1, ROWS);
}

void close() {
	if (restoreConsole()) {
		errorMessage("chyba pri zavirani konzole");
		exit(-1);
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
		for (unsigned int c = 0; choice[c] != '\0'; c++) printf_s("%c", choice[c]);
	}
	va_end(choices);
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