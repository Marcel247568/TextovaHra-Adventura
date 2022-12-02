#pragma once
#include <stdarg.h>
#include <stdbool.h>

void setup(const char* name, unsigned int columns, unsigned int rows);
void close();

void errorMessage(const char* message);
void quickMessage(const char* message);

void printMenu(unsigned int column, unsigned int row, unsigned int count, ...);
void printInputBox();
void printArtFile(const char* file, unsigned int column, unsigned int row);
void printTextFile(const char* file, unsigned int part, bool instant, unsigned int row);

void mSleep(unsigned int s);
bool boolAnswer();
unsigned int numAnswer(unsigned int from, unsigned int to);

void clearScreen();