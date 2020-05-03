#pragma once
#ifndef _Pacman_H_
#define _Pacman_H_
#include <conio.h>
#include "Map.h"
#include "GameClass.h"
#include "Menu.h"
#define size_map_y 22
#define size_map_x 26
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_DOWN 80

enum Motion {
	STOP,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Map;
class Fruit;
class Monster;
class GameClass;
class Menu;

class Pacman
{
	int x;
	int y;
	int score_coin = 0;
	int life = 3;
	Motion pacman_motion;
public:
	void input_move();
	void deth_by_monster();
	void setup_pacman();
	void pacman_move();
	void teleport();
	friend class Map;
	friend void draw_timer_score_life();
	friend class Fruit;
	friend class Menu;
};

extern Map board;
extern Monster monsterZ, monsterM, monsterN;
extern GameClass game;
extern Pacman pacman;
#endif
