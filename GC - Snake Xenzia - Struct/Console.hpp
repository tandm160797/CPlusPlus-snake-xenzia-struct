#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>

enum Color
{
	BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PINK, DARK_YELLOW, DARK_WHITE, GREY, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE
};
enum DirectionKey
{
	KEY_UP = 1072,
	KEY_DOWN = 1080,
	KEY_LEFT = 1075,
	KEY_RIGHT = 1077,
	KEY_NONE = -1
};

int inputKey();
void clrscr();
void gotoXY(int x, int y);
int whereX();
int whereY();
void noCursorType();
void setTextColor(Color color);
void setTitle(char *title);
void resizeCsl(int width, int height);