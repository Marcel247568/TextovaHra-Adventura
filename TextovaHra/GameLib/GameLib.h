#pragma once
#include <stdarg.h>
#include <stdbool.h>

void errorMessage(const char* message);
void quickMessage(const char* message);
void staticMessage(const char* message);

void setup(const char* name, unsigned int columns, unsigned int rows);
void close();
void printMenu(unsigned int column, unsigned int row, unsigned int count, ...);
void printInputBox();
bool boolAnswer();
unsigned int numAnswer(unsigned int from, unsigned int to);
void clearScreen();
void printArtFile(const char* file, unsigned int column, unsigned int row);
void printTextFile(const char* file, unsigned int part, unsigned int row);