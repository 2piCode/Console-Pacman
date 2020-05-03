#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include "Pacman.h"
#include <windows.h>
#include "GameClass.h"

void draw_timer_score_life();

extern GameClass game;
extern Pacman pacman;
extern HANDLE hStdOut;