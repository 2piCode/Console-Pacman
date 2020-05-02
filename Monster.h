#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#define size_map_y 22
#define size_map_x 26

class Monster
{
	int x;
	int y;
	int side_move = 5;
	int stopwatch_enter_monster_sec = 0;
public:
	void setup_monster(Monster& enemy);
	void setup_enter_monster_time();
	void monster_move();
	void enter_monster();
	friend void draw_map();
};

extern Monster monsterZ;
extern Monster monsterN;
extern Monster monsterM;
extern int second;
extern int minute;
extern char map[size_map_y][size_map_x];
