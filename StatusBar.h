#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include "Pacman.h"
#include <windows.h>

void draw_timer_score_life();

extern int second;
extern int minute;
extern int hour;
extern Pacman pacman;
extern HANDLE hStdOut;