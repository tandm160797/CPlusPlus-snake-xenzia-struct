#pragma once
#include "Console.hpp"
#include <iostream>
#include <ctime>
using namespace std;

#define TOP_WALL 2
#define BOT_WALL 22
#define LEFT_WALL 10
#define RIGHT_WALL 69
//
#define HEAD_SNAKE 1
#define BODY_SNAKE 15
#define FOOD 3

enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

struct Position
{
	int x, y;
};
struct Snake
{
	Position* position;
	int size;
};

typedef Position Food;
bool operator==(Position positionLeft, Position positionRight);

Snake initialSnake(int size, Direction direction);
Food initialFood();
Position nodeEnd(Snake snake);
//
bool isEatFood(Snake snake, Food food);
bool isErrorFood(Snake snake, Food food);
bool isLose(Snake snake);
//
void drawWall();
void drawFood(Food food);
void drawSnake(Snake snake);
void displayScore(int score);
void deleteNode(Position node);
void pollEvent(Direction &direction);
void pushBack(Snake &snake);
void actionLose();
void move(Snake snake, Direction direction);
void run();
