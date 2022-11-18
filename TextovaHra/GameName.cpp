#include "GameName.h"
#include "ANSI.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned int COLUMNS;
static unsigned int ROWS;

void errorMessage(const char* message) {
	setStyle(1, DEFAULT_STYLE);
	setColor(BRIGHT_FOREGROUND, RED);
	printf_s("\nERROR: ");
	setColor(FOREGROUND, DEFAULT_COLOR);
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
}

void printMenu(unsigned int count, ...) {
	va_list choices;
	va_start(choices, count);

	const char* choice;
	for (unsigned int n = 0; n < count; n++) {
		choice = va_arg(choices, const char*);
		printf("%u: ", n+1);
		for (unsigned int c = 0; choice[c] != '\0'; c++) printf_s("%c", choice[c]);
		printf_s("\n");
	}
}