#pragma once
#include <iostream>
#define size_map_y 22
#define size_map_x 26

class Fruit
{
	int x;
	int y;
public:
	void setup_spawn_fruit();
	//void spawn_new_fruit();
	friend void draw_map();
};

extern char map[size_map_y][size_map_x];