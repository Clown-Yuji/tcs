#include <iostream>
#include "snake.h"

void InitWall(void)
{
	for (size_t i = 0; i <= HIGH; i++)
	{
		for (size_t j = 0; j <= WIDE; j++)
		{
			if (j == WIDE)
			{
				std::cout << "|" << std::ends;
			}
			else if (i == HIGH)
			{
				std::cout << "_" << std::ends;
			}
			else
			{
				std::cout << " " << std::ends;
			}
		}
		std::cout << "\n" << std::ends;
	}
}

void PlayGame(void)
{
	char key = 'd';
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE 
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		InitUI();
		if (_kbhit())
		{
			key = _getch();
		}
		switch (key)
		{
		case 'w':kx = 0; ky = -1; break;
		case 's':kx = 0; ky = +1; break;
		case 'a':kx = -1; ky = 0; break;
		case 'd':kx = +1; ky = 0; break;
		default:
			break;
		}
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;
			}
		}
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			InitFood();
			snake.size++;
			score += 10;
			speed -= 10;
		}
		LastX = snake.body[snake.size - 1].X;
		LastY = snake.body[snake.size - 1].Y;
		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += kx;
		snake.body[0].Y += ky;
		Sleep(speed);
	}
	return;
}
void ShowScore(void)
{
	COORD coord;
	coord.X = 0;
	coord.Y = HIGH + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
	LOG("game over!");
	LOG(score);
}

int main(void)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	std::srand(time(NULL));

	InitSnake();
	InitFood();

	InitWall();
	InitUI();
	PlayGame();
	ShowScore();


	std::cin.get();
}

void InitSnake(void)
{
	snake.size = 2;

	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;
}
void InitFood(void)
{
	food.X = std::rand() % WIDE;
	food.Y = std::rand() % HIGH;
}
void InitUI(void)
{
	COORD coord = { 0 };
	for (size_t i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if (i == 0)
		{
			putchar('@');
		}
		else
		{
			putchar('*');
		}
	}
	coord.X = LastX;
	coord.Y = LastY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}