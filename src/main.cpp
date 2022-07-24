#include "compati_stuff.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <list>
#include <thread>
#include <clocale>

// four kind of direction
enum class dir4 :unsigned {
	forward = 0u,
	backward,
	left_toward,
	right_toward
};

enum class element :unsigned char {
	blank = 0u,
	head,
	body,
	food
};

// width of field
constexpr unsigned char width = 15;
// length of field
constexpr unsigned char length = 15;

constexpr position spawnPoint = { length / 2 + length % 2,width / 2 + width % 2 };

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

void Move(position& pos, dir4 dir) {
	switch (dir)
	{
	case dir4::forward:
		pos.y--;
		if (pos.y < 0)
			pos.y = length - 1;
		break;
	case dir4::backward:
		pos.y++;
		if (pos.y > length - 1)
			pos.y = 0;
		break;
	case dir4::left_toward:
		pos.x--;
		if (pos.x < 0)
			pos.x = width - 1;
		break;
	case dir4::right_toward:
		pos.x++;
		if (pos.x > width - 1)
			pos.x = 0;
		break;
	}
}

void PrintField() {
	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < width; j++)
			putwchar(L"¡õ¡ñ¡ö¡î"[unsigned(field[i][j])]);
		putchar('\n');
	}
	printf("current score: %d", score);
}

int main() {
	setlocale(LC_CTYPE, "");
	srand(unsigned(time(NULL)));

	std::list<dir4> dirQuque;

	dir4 curDir, dirRec;
	curDir = dirRec = dir4::forward;

	position foodPos = { rand() % length,rand() % width };
	position tail = spawnPoint, head = spawnPoint;

	field[foodPos.y][foodPos.x] = element::food;

	int snakeLength = 1;
	unsigned pauseTime = 100u;

	char got = '\0';

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);


	// main loop
	while (true) {
		if (keyboard_hit()) {

			switch (getchar_no_echo()) {
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
				pauseTime = pauseTime / 2;
		}
	out_of_chk:
		dirQuque.push_back(curDir);

		position before = head;
		// move
		Move(head, curDir);
		switch (field[head.y][head.x])
		{
		case element::blank:
			field[head.y][head.x] = element::head;
			field[before.y][before.x] = element::body;
			field[tail.y][tail.x] = element::blank;
			Move(tail, dirQuque.front());
			dirQuque.pop_front();
			break;
		case element::body:
			clear_screen_no_sparkle(consoleHandle);
			puts("GAME OVER!\n");
			printf("Finally score: %d", score);
			system("pause");
			exit(0);
		case element::food:
			field[before.y][before.x] = element::body;
			field[head.y][head.x] = element::head;
			snakeLength++;
			score += 100;
			foodPos = { short(rand() % length),short(rand() % width) };
			field[foodPos.y][foodPos.x] = element::food;
			break;
		}

		PrintField();
		std::this_thread::sleep_for(std::chrono::milliseconds(pauseTime));
		clear_screen_no_sparkle(consoleHandle);
	}
	return 0;
}
