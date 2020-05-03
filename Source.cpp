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
#define size_map_y 22
#define size_map_x 26

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool lose, win;

int second = 0, hour = 0, minute = 0;

int num_coin = 202;

Pacman pacman;
Fruit fruit;
Monster monsterZ, monsterN, monsterM;
Map board;

void win_by_coin() {
	if (num_coin == 0) win = true;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	bool people_exit = false;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\tWelcome to the Pacman console game" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
	SetConsoleTextAttribute(hStdOut, BACKGROUND_INTENSITY);
	std::cout << "\t\t\t\t\t\tSTART GAME";
	while (!people_exit) {
		//update_map(map);
		while (!_kbhit());
		SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
		system("cls");
		setup();
		while (lose == false and win == false) {
			draw_timer_score_life();
			board.draw_map();
			board.collected_coin();
			pacman.input_move();
			pacman.pacman_move();
			pacman.teleport();
			monsterZ.enter_monster();
			monsterN.enter_monster();
			monsterM.enter_monster();
			monsterZ.monster_move();
			monsterN.monster_move();
			monsterM.monster_move();
			fruit.spawn_new_fruit();
			pacman.deth_by_monster();
			win_by_coin();
			system("cls");
		}
		if (win == true) {
			system("cls");
			SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
			std::cout << "\t\t\t\t\t\tCONGRATULATIONS!!!" << std::endl;
			std::cout << "\t\t\t\t\t\t   YOU WIN!!!" << std::endl;
			std::cout << "\t\t\t\t||===========================================||";
		}
		else if (lose == true) {
			system("cls");
			SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
			std::cout << "\t\t\t\t\t\t    YOU LOSE!" << std::endl;
			std::cout << "\t\t\t\t||===========================================||" << std::endl;
		}
		lose = false; win = false;
	}
	return 0;
}


