/*
	source file: main.cpp

	Copyright (c) 2022 TheCryStal, All rights reserved.

	MIT License
*/


#include <cstdlib>
#include <queue>
#include <thread>
#include <clocale>

#include <conio.h>
#include <Windows.h>

// four kinds of direction
enum class dir4 :unsigned {
	forward = 0u,
	backward,
	left_toward,
	right_toward
};

// element appers in field
enum class element :unsigned char {
	blank = 0u,
	head,
	body,
	food
};

// width of field
constexpr unsigned char width = 5;
// length of field
constexpr unsigned char length = 5;

constexpr COORD spawnPoint = { length / 2 + length % 2,width / 2 + width % 2 };

// Array is kind of Hash so it is high-effective
constexpr dir4 dirOppositeImg[4] = {
	dir4::backward,
	dir4::forward,
	dir4::right_toward,
	dir4::left_toward
};

// game field, all gaming data will record on it
element field[length][width] = { {} };

unsigned score = 0u;

void Move(COORD& pos, dir4 dir) {
	switch (dir)
	{
	case dir4::forward:
		pos.Y--;
		if (pos.Y < 0)
			pos.Y = length - 1;
		break;
	case dir4::backward:
		pos.Y++;
		if (pos.Y > length - 1)
			pos.Y = 0;
		break;
	case dir4::left_toward:
		pos.X--;
		if (pos.X < 0)
			pos.X = width - 1;
		break;
	case dir4::right_toward:
		pos.X++;
		if (pos.X > width - 1)
			pos.X = 0;
		break;
	}
}

void PrintField() {
	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < width; j++)
			putwchar(L"□●■☆"[unsigned(field[i][j])]);
		putchar('\n');
	}
	printf("current score: %d", score);
}

int main() {
	setlocale(LC_CTYPE, "");
	srand(unsigned(time(NULL)));

	std::queue<dir4> dirQueue;

	dir4 curDir, dirRec;
	curDir = dirRec = dir4::forward;

	COORD foodPos = { rand() % length,rand() % width };
	COORD tail = spawnPoint, head = spawnPoint;

	field[foodPos.Y][foodPos.X] = element::food;

	int snakeLength = 1;
	unsigned tick = 100u;

	char got = '\0';

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	{ // 'cci' is used only once, so pop it after use
		CONSOLE_CURSOR_INFO cci = { 1,false };
		SetConsoleCursorInfo(hConsole, &cci);
	}

	// main loop
	while (true) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
			case 'W':
				dirRec = dir4::forward;
				break;
			case 'a':
			case 'A':
				dirRec = dir4::left_toward;
				break;
			case 's':
			case 'S':
				dirRec = dir4::backward;
				break;
			case 'd':
			case 'D':
				dirRec = dir4::right_toward;
				break;
			default:
				goto out_of_chk;
				break;
			}
			if (snakeLength == 1 && dirOppositeImg[(size_t)dirRec] == curDir ||
				dirOppositeImg[size_t(dirRec)] != curDir)
				curDir = dirRec;
			else if (dirRec == curDir)
				tick = tick / 2;
		}
	out_of_chk:
		dirQueue.push(curDir);

		COORD before = head;
		// move
		Move(head, curDir);
		switch (field[head.Y][head.X])
		{
		case element::blank:
			field[head.Y][head.X] = element::head;
			field[before.Y][before.X] = element::body;
			field[tail.Y][tail.X] = element::blank;
			Move(tail, dirQueue.front());
			dirQueue.pop();
			break;
		case element::body:
			system("cls");
			puts("GAME OVER!\n");
			printf("Finally score: %d\n", score);
			system("pause");
			return 0;
		case element::food:
			field[before.Y][before.X] = element::body;
			field[head.Y][head.X] = element::head;
			snakeLength++;
			score += 100;

			do {
				foodPos = { short(rand() % length),short(rand() % width) };
			} while (field[foodPos.Y][foodPos.X] != element::blank);

			field[foodPos.Y][foodPos.X] = element::food;
			break;
		}

		PrintField();
		Sleep(tick);
		SetConsoleCursorPosition(hConsole, { 0,0 });
	}
	return 0;
}