#pragma once
#include <stdarg.h>

void errorMessage(const char* message);

void setup(const char* name, unsigned int columns, unsigned int rows);
void printIntro();
void printMenu(unsigned int count, ...);