#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define LOG(x) std::cout << x << std::endl;

#define WIDE 60
#define HIGH 20

struct BODY
{
	int X, Y;
};
struct SNAKE
{
	struct BODY body[WIDE * HIGH];
	int size;
};
struct FOOD
{
	int X, Y;
};


SNAKE snake;
FOOD food;


int score = 0;
int LastX = 0;
int LastY = 0;
int speed = 100;
int kx = 0;
int ky = 0;

void InitSnake(void);
void InitFood(void);
void InitUI(void);
void PlayGame(void);
void InitWall(void);
void ShowScore(void);