// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "ANSI.h"

using namespace std;

int main()
{
	//setup console 80 x 20 characters
	if (setupConsole(80, 20)) return -1;

	//set window title
	char title[] = "TextGame";
	setWindowTitle(title);
	
	//changing colors
	setColor(FOREGROUND, BLUE);
	setColor(BRIGHT_BACKGROUND, YELLOW);
	
	//set text style
	setStyle(2, BOLD, UNDERLINE);

	//save and restore cursor position
	saveCursorPosisiton();
	restoreCursorPosition();

	//relative cursor position
	relativeCursorPosition(10, -3);

	//absolute cursor position
	absoluteCursorPosition(15, 17);
	absoluteCursorPosition(0, 19);

	//change cursor shape
	shapeCursor(BLOCK);

	//blink or hide cursor
	blinkCursor(1);
	hideCursor(0);

	//scroll margins
	scrollMargins(5, 20);

	if (restoreConsole()) return -1;
	getchar();
	return 0;
}