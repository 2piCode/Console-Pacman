#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
using namespace std;


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool lose, win;

int second = 0, hour = 0, minute = 0;

const int size_map_y = 22;
const int size_map_x = 26;
int score = 0;
int num_coin = 187;
char map[size_map_y][size_map_x]{
"BBBBBBBBBBBBBBBBBBBBBBBBB",//0					
"B'''''''''''B'''''''''''B",//1					
"B'BBB'BBBBB'B'BBBBB'BBB'B",//2					
"B'BBB'BBBBB'B'BBBBB'BBB'B",//3					
"B'''''''''''''''''''''''B",//4					
"B'BBB'B'BBBBBBBBB'B'BBB'B",//5					
"B'''''B'''''B'''''B'''''B",//6					
"BBBBB'BBBB  B  BBBB'BBBBB",//7					
"    B'B           B'B   ",//8					
"BBBBB'B  BB---BB  B'BBBBB",//9					
"     '   B ZNM B   '     ",//10				
"BBBBB'B  BBBBBBB  B'BBBBB",//11				
"    B'B           B'B    ",//12			
"BBBBB'B  BBBBBBB  B'BBBBB",//13			
"B'''''''''''B'''''''''''B",//14		
"B'BBB'BBBBB'B'BBBBB'BBB'B",//15			
"B'''B'''''''''''''''B'''B",//16		
"BBB'B'B''BBBBBBB''B'B'BBB",//17			
"B'''''B'''''B'''''B'''''B",//18		
"B'BBBBBBBB''B''BBBBBBBB'B",//19		
"B'''''''''''''''''''''' B",//20		
"BBBBBBBBBBBBBBBBBBBBBBBBB",//21		
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
	int x;
	int y;
};

struct Fruit {
	int x;
	int y;
};

struct Enemy {
	int x;
	int y;
};

Pacman pacman;
Fruit fruit;
Enemy z, n, m;

void setup() {
	lose = false;
	win = false;
	pacman_motion = STOP;
	pacman.x = 23;
	pacman.y = 20;
	fruit.x = rand() % (size_map_x);
	fruit.y = rand() % (size_map_y);
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x - 1); j++) {
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == 'Z') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*/) {
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
	cout << "Time: " << hour << " : " << minute << " : " << second << "\tCollected " << score << " of 187" << "\tLeft: " << num_coin << endl;
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
			else if (map[i][j] == 'M') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "L";
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
		fruit.x = rand() % size_map_x;
		fruit.y = rand() % size_map_y;
	}
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x - 1); j++) {
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == '-') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*/) {
				fruit.x = rand() % (size_map_x - 1);
				fruit.y = rand() % size_map_y;
			}
		}
	}
	if (pacman.x == 0 and pacman.y == 10) {
		pacman.x = 24;
		map[10][0] = ' ';
	}
	else if (pacman.x == 24 and pacman.y == 10) {
		pacman.x = 1;
		map[10][24] = ' ';
	}
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (pacman.y == i and pacman.x == j  and map[i][j] == '\'' ) {
				score++;
				num_coin--;
			}
		}
	}
}

void win_by_coin() {
	if (num_coin == 0) win = true;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	setup();
	while (lose == false or win == false) {
		draw_timer_score();
		drawMap();
		input();
		logic();
		win_by_coin();
		system("cls");
	}
	if (win == true) {
		cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tCONGRATULATIONS!!!" << endl;
		cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tYOU WIN!!!" << endl;
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