#pragma once
#include <iostream>
#include <windows.h>
#include "GameClass.h"
#include "Pacman.h"
#include "Monster.h"

class GameClass;
class Pacman;
class Monster;

class Menu
{
	char* name[200];
	int item = 3;
	int active = 0;
public:
	void set_name();
	void set_name_end();
	void draw_menu();
	void draw_menu_end(bool win);
	void active_item();
	void check_active();
};

extern Menu menu;
extern GameClass game;
extern Pacman pacman;
extern Monster monsterZ, monsterN, monsterM;