#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include <Windows.h>
#include <conio.h>
#include <locale>

// Copy from https://docs.microsoft.com/zh-cn/windows/console/clearing-the-screen Instance 3
// Modified some parts of the source code
void cls() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD writtenWord = 0;

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	if (!FillConsoleOutputAttribute(
		hStdout,
		csbi.wAttributes,
		csbi.dwSize.X * csbi.dwSize.Y,
		{ 0,0 },
		&writtenWord))
		return;

	SetConsoleCursorPosition(hStdout, { 0,0 });
}

struct Position {
	int x;
	int y;
};

#include <iostream>

using namespace std;

#define FORWARD 3
#define LEFT_TOWARD 2
#define RIGHT_TOWARD 1
#define BACKWARD 0

const int directionsImage[4] = {
FORWARD,
LEFT_TOWARD,
RIGHT_TOWARD,
BACKWARD
};

void Move(int direction, Position* pos) {

	switch (direction)
	{
	case FORWARD:
		pos->y--;
		if (pos->y < 0)
			pos->y = FIELD_LENGTH - 1;
		break;
	case BACKWARD:
		pos->y++;
		if (pos->y > FIELD_LENGTH)
			pos->y = 0;
		break;
	case LEFT_TOWARD:
		pos->x--;
		if (pos->x < 0)
			pos->x = FIELD_WIDTH - 1;
		break;
	case RIGHT_TOWARD:
		pos->x++;
		if (pos->x > FIELD_WIDTH)
			pos->x = 0;
		break;
	default:
		fputs("unknown direction, program exited, code: 1", stderr);
		exit(1);
	}
}

struct SnakeNode {
	// is it necessary?
	Position nodePos;
	int direction;
};

void NodeInit(SnakeNode* dst, Position srcPos, int srcDirection) {
	dst->direction = srcDirection;
	dst->nodePos = srcPos;
}

int field[FIELD_LENGTH][FIELD_WIDTH];

const int blank = 0;
const int head = 1;
const int body = 2;
const int food = 3;

void FieldPrint(int src[FIELD_LENGTH][FIELD_WIDTH]) {
	for (int i = 0; i < FIELD_LENGTH; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++)
			wcout << L"¡õ¡ñ¡ö¡î"[src[i][j]];

		wcout << endl;
	}
}


#endif // SNAKE_H
