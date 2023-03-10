#include "cls.h"
#include <iostream>
#include <windows.h>
#include "cls.h"

void cls() {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	std::cout.flush();

	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	SetConsoleCursorPosition(hOut, topLeft);
}
