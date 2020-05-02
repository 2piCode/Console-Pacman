#pragma once
#ifndef _Pacman_H_
#define _Pacman_H_
#include <conio.h>
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

class Pacman {
	int x;
	int y;
	Motion pacman_motion;
public:
	void input_move();
//	void deth_by_monster();
	void setup_pacman();
	void pacman_move();
	void teleport();
	friend void spawn_new_fruit();
	friend void draw_map();
};

extern char map[size_map_y][size_map_x];

#endif


