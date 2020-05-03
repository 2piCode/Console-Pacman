#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include "Map.h"
#include "GameClass.h"
#include "Menu.h"
#define size_map_y 22
#define size_map_x 26

class Map;
class GameClass;
class Pacman;
class Menu;

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
	void monster_enter();
	void teleport();
	void all_monster_enter();
	void all_monster_move();
	void all_monster_teleport();
	friend class Map;
	friend class Pacman;
	friend class Menu;

};
extern Monster monsterZ;
extern Monster monsterN;
extern Monster monsterM;
extern GameClass game;
