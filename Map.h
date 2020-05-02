#pragma once
#include <iostream>
#include <windows.h>
#include "Pacman.h"
#include "Monster.h"
#include "Fruit.h"
#define size_map_y 22
#define size_map_x 26

void draw_map();

extern char map[size_map_y][size_map_x];
extern HANDLE hStdOut;
extern Pacman pacman;
extern Monster monsterZ;
extern Monster monsterN;
extern Monster monsterM;
extern Fruit fruit;