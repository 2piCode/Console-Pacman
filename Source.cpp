#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include "Pacman.h"
#include "Monster.h"
#include "Fruit.h"
#include "Map.h"
#include "StatusBar.h"
#include "Setup.h"
#include "GameClass.h"
#include "Menu.h"
#define size_map_y 22
#define size_map_x 26

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

Pacman pacman;
Fruit fruit;
Monster allMonster, monsterZ, monsterN, monsterM;
Map board;
GameClass game;
Menu menu;

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	//goto chiter;
	ShowConsoleCursor(FALSE);
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	menu.draw_menu();
	menu.check_active();
	system("cls");
	while (true) {
		board.update_map();
		SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
		setcur(0, 0);
		setup();
		while (game.lose == false and game.win == false) {
			draw_timer_score_life();
			board.draw_map();
			pacman.input_move();
			pacman.pacman_move();
			pacman.teleport();
			allMonster.all_monster_enter();
			allMonster.all_monster_move();
			allMonster.all_monster_teleport();
			fruit.spawn_new_fruit();
			pacman.deth_by_monster();
			game.win_by_coin();
			Sleep(45);
			setcur(0, 0);
		}
	//chiter:
		system("cls");
		setcur(0, 0);
		menu.draw_menu_end(game.win);
		menu.check_active();
		system("cls");
	}
	return 0;
}


