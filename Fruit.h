#pragma once
#include <iostream>
#include "Map.h"
#define size_map_y 22
#define size_map_x 26

class Map;

class Fruit
{
	int x;
	int y;
public:
	void setup_spawn_fruit();
	void spawn_new_fruit();
	friend class Map;
};

extern Map board;
