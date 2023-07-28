/*
	source file: main.cpp

	Copyright (c) 2022 TheCryStal, All rights reserved.

	MIT License
*/

#include "macros.h"

#include <array>
#include <iostream>
#include <queue>
#include <thread>

#include <Windows.h>
#include <conio.h>

#define ERROR_ATTRI   \
	TF_FMT(TF_FG_RED) \
	TF_FMT(TF_BG_DEFAULT)

using std::wcout;
using std::wclog;
using std::wcerr;
using std::endl;

using std::array;
using std::wstring;

using namespace std::chrono_literals;

// four kinds of direction
enum class dir4 : unsigned {
	forward = 0u,
	backward,
	left_toward,
	right_toward
};

// element appers in field
enum class element : unsigned char {
	blank = 0u,
	head,
	body,
	food
};

// Array is kind of Hash so it is high-effective
constexpr dir4 dirOppositeImg[4] = {
		dir4::backward,
		dir4::forward,
		dir4::right_toward,
		dir4::left_toward};

constexpr unsigned g_Width = 25;
constexpr unsigned g_Length = 25;

// game field, all gaming data will record on it
std::array<std::array<element, g_Width>, g_Length> g_View = {};

unsigned long long g_Score = 1;

bool g_HasFood = false;

void Move(COORD &pos, dir4 dir) {
	switch (dir) {
		case dir4::forward:
			pos.Y--;
			if (pos.Y < 0)
				pos.Y = g_Length - 1;
			break;
		case dir4::backward:
			pos.Y++;
			if (pos.Y > g_Length - 1)
				pos.Y = 0;
			break;
		case dir4::left_toward:
			pos.X--;
			if (pos.X < 0)
				pos.X = g_Width - 1;
			break;
		case dir4::right_toward:
			pos.X++;
			if (pos.X > g_Width - 1)
				pos.X = 0;
			break;
	}
}

void PrintField() {
	wcout << TF_BG_EXT_RGB_SEQ("114", "191", "200") << TF_FMT(TF_FG_MAGENTA);
	
	for (auto i : g_View) {
		for (auto j : i) {
			wcout << array<wstring, 4>({wstring(L"  "),
										wstring(W(TF_FMT(TF_BG_YELLOW) "  " TF_BG_EXT_RGB_SEQ("114", "191", "200"))),
										wstring(W(TF_FMT(TF_BG_YELLOW) "  " TF_BG_EXT_RGB_SEQ("114", "191", "200"))),
										wstring(W(TF_FMT(TF_BG_RED) "  " ))})[size_t(j)];
		}
		wcout << endl;
	}

	wcout << TF_FMT(TF_BG_DEFAULT) << TF_FMT(TF_FG_DEFAULT)
		  << "Press WASD to move." << endl
		  << "Press <ESC> to exit." << endl;
}

int main() {
	wcout.imbue(std::locale("", std::locale::ctype));
	srand((unsigned) time(NULL));
	constexpr COORD spawnPoint = {g_Width / 2 - 1, g_Length / 2 - 1};
	std::chrono::milliseconds tick = 50ms;

	std::queue<dir4> dirQueue;
	auto out = GetStdHandle(STD_OUTPUT_HANDLE);

	dir4 curDir, dirRec;
	curDir = dirRec = dir4::forward;

	COORD tail = spawnPoint, head = spawnPoint;

	if (out == INVALID_HANDLE_VALUE) {
		wcerr << ERROR_ATTRI
			  << "Failed to call GetStdHandle, error code: " << GetLastError() << endl
			  << TF_FMT(TF_FG_DEFAULT);
		return 0;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(out, &dwMode)) {
		wcerr << "Failed to call GetConsoleMode, error code: " << GetLastError() << endl;
		return 0;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(out, dwMode)) {
		wcerr << ERROR_ATTRI << "Failed to call SetConsoleMode, error code: " << GetLastError() << endl
			  << TF_FMT(TF_FG_DEFAULT);
		return 0;
	}

	wclog << CSI "?1049h" << CSI "?12l" << CSI "?25l";

	CONSOLE_SCREEN_BUFFER_INFO info = {};

	if (!GetConsoleScreenBufferInfo(out, &info)) {
		wcerr << ERROR_ATTRI
			  << "Failed to call GetConsoleScreenBufferInfo, error code: "
			  << GetLastError() << endl
			  << TF_FMT(TF_FG_DEFAULT);
		return 0;
	}

	auto attri = info.wAttributes;

	// main loop
	while (true) {
		tick = 50ms;
		if (!g_HasFood) {
			size_t x, y;
			element *temp;
			do {
				x = rand() % 25;
				y = rand() % 25;
				temp = &g_View[x][y];
			} while (*temp != element::blank);
			*temp = element::food;
			g_HasFood = true;
		}
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
				case VK_ESCAPE:
					wclog << CSI "?1049l";
					system("cls");
					return 0;
				default:
					goto out_of_chk;
					break;
			}
			if (g_Score == 1 && dirOppositeImg[(size_t) dirRec] == curDir || dirOppositeImg[size_t(dirRec)] != curDir)
				curDir = dirRec;
			else if (dirRec == curDir)
				tick = tick / 2;
		}
	out_of_chk:
		COORD before = head;
		dirQueue.push(curDir);
		// move
		Move(head, curDir);
		switch (g_View[head.Y][head.X]) {
			case element::blank:
				g_View[head.Y][head.X] = element::head;
				g_View[before.Y][before.X] = element::body;
				g_View[tail.Y][tail.X] = element::blank;
				Move(tail, dirQueue.front());
				dirQueue.pop();
				break;
			case element::body:
				system("cls");
				wclog << TF_FMT(TF_FG_CYAN)
					  << TF_FMT(TF_BG_DEFAULT)
					  << "Game over!" << endl
					  << "Final score:" << g_Score << TF_FMT(TF_FG_DEFAULT) << endl;
				system("pause");
				return 0;
			case element::food:
				g_View[before.Y][before.X] = element::body;
				g_View[head.Y][head.X] = element::head;
				g_Score++;
				g_HasFood = false;
				break;
		}

		PrintField();
		SetConsoleCursorPosition(out, {0, 0});
		std::this_thread::sleep_for(tick);
	}

	SetConsoleTextAttribute(out, attri);
	system("pause");
	return 0;
}