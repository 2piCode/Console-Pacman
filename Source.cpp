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

int second = 0, hour = 0, minute = 0, stopwatch_enter_monster_sec = 0, life = 3;
const int size_map_y = 22;
const int size_map_x = 26;

int score = 0;
int num_coin = 202;

char map[size_map_y][size_map_x]{
"|-----------------------|",//0					
"|'''''''''''|'''''''''''|",//1					
"|'|||'|||||'|'|||||'|||'|",//2					
"|'|||'|||||'|'|||||'|||'|",//3					
"|'''''''''''''''''''''''|",//4					
"|'|||'|'---------'|'|||'|",//5					
"|'''''|'''''|'''''|'''''|",//6					
"|----'|---  |  ---|'-----",//7					
"    |'|           |'|   ",//8					
"-----'|  |-----|  |'-----",//9					
"     '   |     |   '     ",//10				
"-----'|  -------  |'-----",//11				
"    |'|           |'|    ",//12			
"-----'|  -------  |'-----",//13			
"|'''''''''''|'''''''''''|",//14		
"|'--|'-----'|'-----'---'|",//15			
"|'''|'''''''''''''''|'''|",//16		
"|--'|'|''-------''|'|'--|",//17			
"|'''''|'''''|'''''|'''''|",//18		
"|'--------''|''--------'|",//19		
"|'''''''''''''''''''''' |",//20		
"|-----------------------|",//21		
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

struct Monster {
	int x;
	int y;
	int side_move = 5;
};

Pacman pacman;
Fruit fruit;
Monster monsterZ, monsterN, monsterM;

void deth_by_monster() {
	if (pacman.y == monsterZ.y and pacman.x == monsterZ.x or
		pacman.y == monsterN.y and pacman.x == monsterN.x or
		pacman.y == monsterM.y and pacman.x == monsterM.x) {
		life--;
		pacman.x = 23;
		pacman.y = 20;
	}
	if (life == 0) lose = true;
}

void win_by_coin() {
	if (num_coin == 0) win = true;
}

void setup_pacman() {
	pacman_motion = STOP;
	pacman.x = 23;
	pacman.y = 20;
}

void setup_monster() {
	monsterZ.x = 11;
	monsterZ.y = 10;
	monsterN.x = 12;
	monsterN.y = 10;
	monsterM.x = 13;
	monsterM.y = 10;
}

void setup_spawn_fruit() {
	fruit.x = rand() % (size_map_x - 3);
	fruit.y = rand() % (size_map_y);
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x); j++) {
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == 'Z') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*/) {
				fruit.x = rand() % (size_map_x - 3);
				fruit.y = rand() % size_map_y;
			}
		}
	}
}

void setup_enter_monster_time() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	int stopwatch_enter_monster_min;
	stopwatch_enter_monster_sec = timeinfo->tm_sec;
	stopwatch_enter_monster_min = timeinfo->tm_min;
	stopwatch_enter_monster_sec += stopwatch_enter_monster_min * 60;
}

void setup() {
	lose = false;
	win = false;

	setup_pacman();
	setup_monster();
	setup_spawn_fruit();
	setup_enter_monster_time();
}

void draw_timer_score_life() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Time: " << hour << " : " << minute << " : " << second;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "\tCollected " << score << " of 202" << "\tLeft: " << num_coin;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	std::cout << "\tLife: " << life << std::endl;
}

void drawMap() {
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (map[i][j] == '|') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "|";
			}
			else if (map[i][j] == '-') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "-";
			}
			else if (i == monsterZ.y and j == monsterZ.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "Z";
			}
			else if (i == monsterN.y and j == monsterN.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "N";
			}
			else if (i == monsterM.y and j == monsterM.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "M";
			}
			else if (i == fruit.y and j == fruit.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
				cout << '0';
			}
			else if (i == pacman.y and j == pacman.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "C";
			}
			else if (map[i][j] == '\'') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << '\'';
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

void pacman_input_move() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': {
			pacman_motion = UP;
			break;
		}
		case 'W': {
			pacman_motion = UP;
			break;
		}
		case 72: {
			pacman_motion = UP;
			break;
		}
		case 'd': {
			pacman_motion = RIGHT;
			break;
		}
		case 'D': {
			pacman_motion = RIGHT;
			break;
		}
		case 77: {
			pacman_motion = RIGHT;
			break;
		}
		case 's': {
			pacman_motion = DOWN;
			break;
		}
		case 'S': {
			pacman_motion = DOWN;
			break;
		}
		case 80: {
			pacman_motion = DOWN;
			break;
		}
		case 'a': {
			pacman_motion = LEFT;
			break;
		}
		case 'A': {
			pacman_motion = LEFT;
			break;
		}
		case 75: {
			pacman_motion = LEFT;
			break;
		}
		}
	}
}

void pacman_move() {
	switch (pacman_motion) {
	case UP: {
		if (map[pacman.y - 1][pacman.x] == ' ' or map[pacman.y - 1][pacman.x] == '\'' or map[pacman.y - 1][pacman.x] == 'Z' or map[pacman.y - 1][pacman.x] == 'M' or map[pacman.y - 1][pacman.x] == 'N') {
			if (map[pacman.y][pacman.x] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				pacman.y--;
			}
			else {
				pacman.y--;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case RIGHT: {
		if (map[pacman.y][pacman.x + 1] == ' ' or map[pacman.y][pacman.x + 1] == '\'' or map[pacman.y][pacman.x + 1] == 'Z' or map[pacman.y][pacman.x + 1] == 'M' or map[pacman.y][pacman.x + 1] == 'N') {
			if (map[pacman.y][pacman.x] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				pacman.x++;
			}
			else {
				pacman.x++;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case DOWN: {
		if (map[pacman.y + 1][pacman.x] == ' ' or map[pacman.y + 1][pacman.x] == '\'' or map[pacman.y + 1][pacman.x] == 'Z' or map[pacman.y + 1][pacman.x] == 'M' or map[pacman.y + 1][pacman.x] == 'N') {
			if (map[pacman.y][pacman.x] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				pacman.y++;
			}
			else {
				pacman.y++;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case LEFT: {
		if (map[pacman.y][pacman.x - 1] == ' ' or map[pacman.y][pacman.x - 1] == '\'' or map[pacman.y][pacman.x - 1] == 'Z' or map[pacman.y][pacman.x - 1] == 'M' or map[pacman.y][pacman.x - 1] == 'N') {
			if (map[pacman.y][pacman.x] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				pacman.x--;
			}
			else {
				pacman.x--;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	}
}

void enter_monster() {
	if (stopwatch_enter_monster_sec == second + minute * 60 - 5 and monsterZ.y == 10 and monsterZ.x == 11) {
		monsterZ.x = 12;
		monsterZ.y = 8;
		monsterZ.side_move = rand() % 4 + 1;
		map[8][11] = ' ';
	}
	else if (stopwatch_enter_monster_sec == second + minute * 60 - 10 and monsterN.y == 10 and monsterN.x == 12) {
		monsterN.x = 12;
		monsterN.y = 8;
		monsterN.side_move = rand() % 4 + 1;
		map[8][11] = ' ';
	}
	else if (stopwatch_enter_monster_sec == second + minute * 60 - 20 and monsterM.y == 10 and monsterM.x == 13) {
		monsterM.x = 12;
		monsterM.y = 8;
		monsterM.side_move = rand() % 4 + 1;
		map[8][11] = ' ';
	}
}

void monster_move(Monster& enemy) {
	switch (enemy.side_move) {
	case 1: {
		if (map[enemy.y - 1][enemy.x] == ' ' or map[enemy.y - 1][enemy.x] == '\'') {
			enemy.y--;

		}
		else {
			enemy.side_move = rand() % 4 + 1;
		}
		break;
	}
	case 2: {
		if (map[enemy.y][enemy.x + 1] == ' ' or map[enemy.y][enemy.x + 1] == '\'') {
			enemy.x++;
		}
		else {
			enemy.side_move = rand() % 4 + 1;
		}
		break;
	}
	case 3: {
		if (map[enemy.y + 1][enemy.x] == ' ' or map[enemy.y + 1][enemy.x] == '\'') {
			enemy.y++;
		}
		else {
			enemy.side_move = rand() % 4 + 1;
		}
		break;
	}
	case 4: {
		if (map[enemy.y][enemy.x - 1] == ' ' or map[enemy.y][enemy.x - 1] == '\'') {
			enemy.x--;
		}
		else {
			enemy.side_move = rand() % 4 + 1;
		}
		break;
	}
	}
}

void spawn_new_fruit() {
	if (pacman.x == fruit.x and pacman.y == fruit.y) {
		fruit.x = rand() % (size_map_x - 3);
		fruit.y = rand() % size_map_y;
	}
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x); j++) {
			while ((fruit.y == i and fruit.x == j and map[i][j] == 'B') or (fruit.y == i and fruit.x == j and map[i][j] == '-') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*/) {
				fruit.x = rand() % (size_map_x - 3);
				fruit.y = rand() % size_map_y;
			}
		}
	}
}

void teleport() {
	if (pacman.x == 0 and pacman.y == 10) {
		pacman.x = 24;
		map[10][0] = ' ';
	}
	else if (pacman.x == 24 and pacman.y == 10) {
		pacman.x = 1;
		map[10][24] = ' ';
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	bool people_exit = false;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\tWelcome to the Pacman console game" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
	SetConsoleTextAttribute(hStdOut, BACKGROUND_INTENSITY);
	std::cout << "\t\t\t\t\t\tSTART GAME";
	while (!people_exit) {
		while (!_kbhit());
		SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
		system("cls");
		setup();
		while (lose == false and win == false) {
			draw_timer_score_life();
			drawMap();
			pacman_input_move();
			pacman_move();
			teleport();
			enter_monster();
			monster_move(monsterZ);
			monster_move(monsterN);
			monster_move(monsterM);
			spawn_new_fruit();
			deth_by_monster();
			win_by_coin();
			system("cls");
		}
		if (win == true) {
			system("cls");
			SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
			std::cout << "\n\n\n\n\n\n\n\t\t\t\t\tCONGRATULATIONS!!!" << std::endl;
			std::cout << "\t\t\t\t\t   YOU WIN!!!" << std::endl;
			std::cout << "\t\t\t\t||===========================================||";
		}
		else if (lose == true) {
			system("cls");
			SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
			std::cout << "\t\t\t\t\t\t    YOU LOSE!" << std::endl;
			std::cout << "\t\t\t\t||===========================================||" << std::endl;
		}
		lose = false; win = false;
	}
	return 0;
}