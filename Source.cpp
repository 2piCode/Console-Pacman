#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool deth;

const int size_map_y = 25;
const int size_map_x = 50;
int score = 0;
char map[size_map_y][size_map_x]{
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                       B                       B",
"B   BBBBB   BBBBBBBBB   B   BBBBBBBBB   BBBBB   B",
"B   BZZZB   BZZZZZZZB   B   BZZZZ Z B   B Z B   B",
"B   BBBBB   BBBBBBBBB   B   BBBBBBBBB   BBBBB   B",
"B                                               B",
"B   BBBBB   B   BBBBBBBBBBBBBBBBB   B   BBBBB   B",
"B           B           B           B           B",
"BBBBBBBBB   BBBBBBBBB   B   BBBBBBBBB   BBBBBBBBB",
"B Z Z Z B   B                       B   B Z Z Z B",
"B Z Z Z B   B   BBBBBBBBBBBBBBBBB   B   B Z Z Z B",
"BBBBBBBBB   B   B               B   B   BBBBBBBBB",
"                B               B                ",
"BBBBBBBBB   B   B               B   B   BBBBBBBBB",
"B Z Z Z B   B   BBBBBBBBBBBBBBBBB   B   B Z Z Z B",
"B Z Z Z B   B                       B   B Z Z Z B",
"BBBBBBBBB   B   BBBBBBBBBBBBBBBBB   B   BBBBBBBBB",
"B                       B                       B",
"B   B B B   BBBBBBBBB   B   BBBBBBBBB   BBBBB   B",
"B       B                               B       B",
" BBB   B   B   BBBBBBBBBBBBBBBBB   B   B   BBBBB ",
"B           B           B           B           B",
"B   BBBBBBBBBBBBBBBBB   B   BBBBBBBBBBBBBBBBB   B",
"B                                               B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

enum Motion {
	STOP,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

Motion pacman_motion;

struct Pacman {
	int x = 47;
	int y = 23;
};

struct Fruit {
	int x;
	int y;
};

Pacman pacman;
Fruit fruit;

void setup() {
	deth = false;
	pacman_motion = STOP;
	pacman.x = 47;
	pacman.y = 23;
	fruit.x = rand() % (size_map_x);
	fruit.y = rand() % (size_map_y);
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (fruit.x == map[i][j] and map[i][j] == 'B' or fruit.x == map[i][j] and map[i][j] == 'Z') {
				fruit.x = rand() % size_map_x;
				fruit.y = rand() % size_map_y;
			}
		}
	}
}

void drawMap() {
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (map[i][j] == 'B') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
				cout << "B";
			}
			else if (map[i][j] == 'Z') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "Z";
			}
			else if (i == pacman.y and j == pacman.x ) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "P";
			}
			else if (i == fruit.y and j == fruit.x ) {
				SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN);
				cout << "0";
			}
			else if (map[i][j] == ' ') cout << " ";
		}
		cout << endl;
	}
	cout << "Score:" << score;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': {
			pacman_motion = UP;
			break;
		}
		case 'd': {
			pacman_motion = RIGHT;
			break;
		}
		case 's': {
			pacman_motion = DOWN;
			break;
		}
		case 'a': {
			pacman_motion = LEFT;
			break;
		}
		}
	}
}

void logic() {
	switch (pacman_motion) {
	case UP:{
		if (map[pacman.y - 1][pacman.x] == ' ') {
			map[pacman.y][pacman.x] = ' ';
			map[pacman.y - 1][pacman.x] = 'P';
			pacman.y--;
		}
		else {
			pacman_motion = STOP;
		}
		break;
		}
	case RIGHT: {
		if (map[pacman.y][pacman.x + 1] == ' ') {
			map[pacman.y][pacman.x] = ' ';
			map[pacman.y][pacman.x + 1] = 'P';
			pacman.x++;
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case DOWN:{
		if (map[pacman.y + 1][pacman.x] == ' ') {
			map[pacman.y][pacman.x] = ' ';
			map[pacman.y + 1][pacman.x] = 'P';
			pacman.y++;
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case LEFT: {
		if (map[pacman.y][pacman.x - 1] == ' ') {
			map[pacman.y][pacman.x] = ' ';
			map[pacman.y][pacman.x - 1] = 'P';
			pacman.x--;
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	
}
	if (pacman.x == fruit.x and pacman.y == fruit.y) {
		score++;
		fruit.x = rand() % size_map_x;
		fruit.y = rand() % size_map_y;
	}
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == 'Z')) {
				fruit.x = rand() % size_map_x;
				fruit.y = rand() % size_map_y;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	setup();
	while (deth == false) {
		drawMap();
		input();
		logic();
		system("cls");
	}
	return 0;
}

/*

SetConsoleTextAttribute(hStdOut,
		BACKGROUND_BLUE | BACKGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "Green\n";*/