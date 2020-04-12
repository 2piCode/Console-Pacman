#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
using namespace std;


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool deth;

int second = 0, hour = 0, minute = 0;

const int size_map_y = 25;
const int size_map_x = 50;
int score = 0;
int num_coin;
char map[size_map_y][size_map_x]{
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",//0
"B'''''''''''''''''''''''B'''''''''''''''''''''''B",//1
"B'''BBBBB'''BBBBBBBBB'''B'''BBBBBBBBB'''BBBBB'''B",//2
"B'''BBBBB'''BBBBBBBBB'''B'''BBBBBBBBB'''BBBBB'''B",//3
"B'''BBBBB'''BBBBBBBBB'''B'''BBBBBBBBB'''BBBBB'''B",//4
"B'''''''''''''''''''''''''''''''''''''''''''''''B",//5
"B'''BBBBB'''B'''BBBBBBBBBBBBBBBBB'''B'''BBBBB'''B",//6
"B''''''''''''B''''''''''B'''''''''''B'''''''''''B",//7
"BBBBBBBBB'''BBBBBBBBB   B   BBBBBBBBB'''BBBBBBBBB",//8
"BBBBBBBBB'''B'''''''''''''''''''''''B'''BBBBBBBBB",//9
"BBBBBBBBB'''B'''BBBBBB-----BBBBBB'''B'''BBBBBBBBB",//10
"BBBBBBBBB'''B'''B               B'''B'''BBBBBBBBB",//11
"''''''''''''''''B    Z N L M    B''''''''''''''''",//12
"BBBBBBBBB'''B'''B               B'''B'''BBBBBBBBB",//13
"BBBBBBBBB'''B'''BBBBBBBBBBBBBBBBB'''B'''BBBBBBBBB",//14
"BBBBBBBBB'''B'''''''''''''''''''''''B'''BBBBBBBBB",//15
"BBBBBBBBB'''B'''BBBBBBBBBBBBBBBBB'''B'''BBBBBBBBB",//16
"B'''''''''''''''''''''''B'''''''''''''''''''''''B",//17
"B'''B'B'B'''BBBBBBBBB'''B'''BBBBBBBBB'''BBBBB'''B",//18
"B'''''''B'''''''''''''''''''''''''''''''B'''''''B",//19
" BBB'''B'''B'''BBBBBBBBBBBBBBBBB'''B'''B'''BBBBB ",//20
"B'''''''''''B'''''''''''B'''''''''''B'''''''''''B",//21
"B'''BBBBBBBBBBBBBBBBB'''B'''BBBBBBBBBBBBBBBBB'''B",//22
"B'''''''''''''''''''''''''''''''''''''''''''''''B",//23
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"//24
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
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == 'Z')) {
				fruit.x = rand() % (size_map_x - 1);
				fruit.y = rand() % size_map_y;
			}
		}
	}
}

void draw_timer_score() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cout << "Time: " << hour << " : " << minute << " : " << second << "\tScore: " << score << endl;
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
			else if (map[i][j] == 'N') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "N";
			}
			else if (map[i][j] == 'L') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "L";
			}
			else if (map[i][j] == 'M') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << "M";
			}
			else if (i == fruit.y and j == fruit.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
				cout << '0';
			}
			else if (i == pacman.y and j == pacman.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "P";
			}
			else if (map[i][j] == '*') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "*";
			}
			else if (map[i][j] == '\'') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "\'";
			}
			else if (map[i][j] == '-') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
				cout << "-";
			}
			else if (map[i][j] == ' ') {
				cout << " ";
			}
		}
		cout << endl;
	}
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
		case 'ц': {
			pacman_motion = UP;
			break;
		}
		}
	}
}

void logic() {
	switch (pacman_motion) {
	case UP: {
		if (map[pacman.y - 1][pacman.x] == ' ' or map[pacman.y - 1][pacman.x] == '\'') {
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
		if (map[pacman.y][pacman.x + 1] == ' ' or map[pacman.y][pacman.x + 1] == '\'') {
			map[pacman.y][pacman.x] = ' ';
			map[pacman.y][pacman.x + 1] = 'P';
			pacman.x++;
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case DOWN: {
		if (map[pacman.y + 1][pacman.x] == ' ' or map[pacman.y + 1][pacman.x] == '\'') {
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
		if (map[pacman.y][pacman.x - 1] == ' ' or map[pacman.y][pacman.x - 1] == '\'') {
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
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == 'Z')) {
				fruit.x = rand() % (size_map_x - 1);
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
		draw_timer_score();
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


	/*second++;
	while (second > 59) {
		second -= 60;
		minute++;
	}
	while (minute > 59) {
		minute -= 60;
		hour++;
	}
	while (hour > 24) {
		hour -= 23;
	}
	cout << "Time: " << hour << " : " << minute << " : " << second << endl;*/