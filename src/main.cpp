// Length of Field, you can also use the constant instead, whatever, they are the same
#define FIELD_LENGTH 15
// Width of Field
#define FIELD_WIDTH 15
#define _USE_UGLY_ARRAY

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER


#include "snake.h"

int main() {
	// initialization
	srand(unsigned(time(NULL)));

	setlocale(LC_ALL, "");

	for (int i = 0; i < FIELD_LENGTH; i++)
		memset((void*)field[i], blank, FIELD_WIDTH);

	SnakeNode snake[FIELD_LENGTH * FIELD_WIDTH];

	Position* tmp = new Position(
		{
			FIELD_LENGTH / 2 + FIELD_LENGTH % 2 - 1 ,
			FIELD_WIDTH / 2 + FIELD_WIDTH % 2 - 1
		});

	NodeInit(snake, *tmp, FORWARD);

	field[tmp->x][tmp->y] = head;

	// got char
	int ch;
	// current Direction of snake head
	int currentDir = FORWARD;
	int snakeLength = 1;
	// food generate
	Position foodPos = { rand() % FIELD_WIDTH,rand() % FIELD_LENGTH };
	field[foodPos.y][foodPos.x] = food;
	int score = 0;
	unsigned pauseTime = 200;

	delete tmp;

	// main loop
	while (true) {

		// display
		FieldPrint(field);
		cout << "score: " << score << endl;
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case 'w':
			case 'W':
				currentDir = FORWARD;
				break;
			case 'a':
			case 'A':
				currentDir = LEFT_TOWARD;
				break;
			case 's':
			case 'S':
				currentDir = BACKWARD;
				break;
			case 'd':
			case 'D':
				currentDir = RIGHT_TOWARD;
				break;
			default:
				goto out_of_chk;
				break;
			}
			if (currentDir == snake->direction)
				pauseTime = 40;
			else if (snake->direction == directionsImage[currentDir] && snakeLength == 1)
				snake->direction = currentDir;
			else if (snake->direction != directionsImage[currentDir])
				snake->direction = currentDir;

		}

	out_of_chk:
		SnakeNode tail = snake[snakeLength - 1];

		Position before = snake->nodePos;
		Move(snake->direction, &snake->nodePos);
		Position after = snake->nodePos;

		switch (field[snake->nodePos.y][snake->nodePos.x])
		{
		case blank:
			snake->nodePos = before;

			// 'i' can be size_t
			for (int i = snakeLength - 2, j = snakeLength - 1; i >= 0; i--, j--)
				snake[j] = snake[i];

			snake->nodePos = after;
			field[before.y][before.x] = body;
			field[tail.nodePos.y][tail.nodePos.x] = blank;
			field[snake->nodePos.y][snake->nodePos.x] = head;
			break;
		case food:
			snake[snakeLength] = tail;
			snakeLength++;
			score += 100;
			snake->nodePos = before;

			// 'i' can be size_t
			for (int i = snakeLength - 2, j = snakeLength - 1; i >= 0; i--, j--)
				snake[j] = snake[i];

			snake->nodePos = after;

			field[after.y][after.x] = head;
			field[before.y][before.x] = body;

			do {
				foodPos = { rand() % FIELD_WIDTH,rand() % FIELD_LENGTH };
			} while (field[foodPos.y][foodPos.x] != blank);
			field[foodPos.y][foodPos.x] = food;

			break;
		case body:
			cout << "YOU DIED!" << endl;
			cout << "GAME OVER!" << endl;
			system("pause");
			return 0;
		default:
			fputs("unknown case was appeared, program exited, code: 1", stderr);
			return 1;
		}


		Sleep(pauseTime);
		pauseTime = 200;

		cls();

	}
	return 0;
}
