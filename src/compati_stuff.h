#pragma once
/*
	header compati_stuff.h

	Copyright (c) 2022 ReverseCRYstal, All rights reserved.

	MIT License

*/

#ifndef COMPATI_STUFF
#define COMPATI_STUFF
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

struct position {
	short x;
	short y;
};

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>

#define keyboard_hit() _kbhit()
#define getchar_no_echo() _getch()

// Copy from https://docs.microsoft.com/zh-cn/windows/console/clearing-the-screen Instance 3
// There are some changes
void clear_screen_no_sparkle(HANDLE hConsole) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD writtenWord = 0;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	if (!FillConsoleOutputAttribute(
		hConsole,
		csbi.wAttributes,
		csbi.dwSize.X * csbi.dwSize.Y,
		{ 0,0 },
		&writtenWord))
		return;

	SetConsoleCursorPosition(hConsole, { 0,0 });
}

#endif // _WIN32
#ifdef __linux__
#include <termios.h>

static int cbuf;

bool _cdecl keyboard_hit() {
	struct termios curtio, oldtio;
	tcgetatrr(0, &oldtio);

}

char _cdecl getchar_no_echo() {
	if (cbuf == NULL)

	else
		return cbuf;
}
#endif // __linux__

#endif // !POSIX_STUFF

