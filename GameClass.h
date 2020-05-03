#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#define KEY_UP 72
#define KEY_ENTER 13
#define KEY_DOWN 80

class GameClass
{
public:
	bool lose;
	bool win;
	int second = 0;
	int hour = 0;
	int minute = 0;
	int num_coin = 202;
	int cursorIndex = 0;
	std::string restart = "RESTART";
	std::string exit = "EXIT";
	void win_by_coin();
	void win_game();
	void lose_game();
	void hello();
	void goodbye();
	void author();
};

extern HANDLE hStdOut;

void setcur(int x, int y);