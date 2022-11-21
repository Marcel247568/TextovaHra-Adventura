#pragma once
#include <stdarg.h>
#include <stdbool.h>

void errorMessage(const char* message);
void quickMessage(const char* message);

void setup(const char* name, unsigned int columns, unsigned int rows);
void printMenu(unsigned int count, ...);
void printInputBox();
bool boolAnswer();
unsigned int numAnswer(unsigned int from, unsigned int to);