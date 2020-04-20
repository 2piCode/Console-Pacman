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

int second = 0, hour = 0, minute = 0, stopwatch_sec = 0, stopwatch_min = 0;

const int size_map_y = 22;
const int size_map_x = 26;
int score = 0;
int num_coin = 202;
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
"     '   B     B   '     ",//10				
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

Motion pacman_motion, enemy_motion_z;

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
	int pos = 5; // выбор направления рандомно
};

Pacman pacman;
Fruit fruit;
Enemy z, n, m;


void deth_by_enemy() {
	lose = true;
}

void win_by_coin() {
	if (num_coin == 0) win = true;
}

void setup() {
	lose = false;
	win = false;
	pacman_motion = STOP;
	pacman.x = 23;
	pacman.y = 20;
	z.x = 11;
	z.y = 10;
	n.x = 12;
	n.y = 10;
	m.x = 13;
	m.y = 10;
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
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	int buf = timeinfo->tm_sec;
	stopwatch_sec = buf;
	buf = timeinfo->tm_min;
	stopwatch_min = buf;
}

void draw_timer_score() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cout << "Time: " << hour << " : " << minute << " : " << second << "\tCollected " << score << " of 202" << "\tLeft: " << num_coin << endl;
}

void drawMap() {
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (map[i][j] == 'B') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
				cout << "B";
			}
			else if (i == z.y and j == z.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "Z";
			}
			else if (i == n.y and j == n.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "N";
			}
			else if (i == m.y and j == m.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				cout << "L";
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

void enter_monster() {
	if (stopwatch_sec == second - 5 and stopwatch_min == minute) {
		z.x = 12;
		z.y = 8;
		z.pos = rand() % 4 + 1;
		map[z.y][z.x] = ' ';
	}
	else if (stopwatch_sec == second - 40 and stopwatch_min == minute) {
		n.x = 12;
		n.y = 8;
	}
	else if (stopwatch_sec == second and stopwatch_min == minute - 1) {
		m.x = 12;
		m.y = 8;
	}
}

void monster_move() {
	//if((map[z.y][z.x + 1] == 'B' and enemy_motion_z == RIGHT) or (map[z.y - 1][z.x] == 'B' and enemy_motion_z == UP) or (map[z.y + 1][z.x] == 'B' and enemy_motion_z == DOWN) or (map[z.y][z.x - 1] == 'B' and enemy_motion_z == LEFT))
		//z.pos = rand() % 5 + 1;
	switch (z.pos) {
	case 1: {
		enemy_motion_z = UP;
		break;
	}
	case 2: {
		enemy_motion_z = RIGHT;
		break;
	}
	case 3: {
		enemy_motion_z = DOWN;
		break;
	}
	case 4: {
		enemy_motion_z = LEFT;
		break;
	}
	case 5: {
		enemy_motion_z = STOP;
		break;
	}
	}
	
	switch (enemy_motion_z) {
	case UP: {
		if (map[z.y - 1][z.x] == ' ' /*or map[z.y - 1][z.x] == 'Z' or map[z.y - 1][z.x] == 'M' or map[z.y - 1][z.x] == 'N'*/) {
			
			map[z.y][z.x] = ' ';
			map[z.y - 1][z.x] = 'Z';
			z.y--;

		}
		else if (map[z.y - 1][z.x] == '\'') {

			map[z.y][z.x] = '\'';
			map[z.y - 1][z.x] = 'Z';
			z.y--;
		}
		else {
			z.pos = rand() % 4 + 1;
		}
		break;
	}
	case RIGHT: {
		if (map[z.y][z.x + 1] == ' ' or map[z.y][z.x + 1] == 'Z' or map[z.y][z.x + 1] == 'M' or map[z.y][z.x + 1] == 'N') {
			map[z.y][z.x] = ' ';
			map[z.y][z.x + 1] = 'Z';
			z.x++;
		}
		else if(map[z.y][z.x + 1] == '\'' ) {
			map[z.y][z.x] = '\'';
			map[z.y][z.x + 1] = 'Z';
			z.x++;
		}
		else {
			z.pos = rand() % 4 + 1;
		}
		break;
	}
	case DOWN: {
		if (map[z.y + 1][z.x] == ' ' or map[z.y + 1][z.x] == 'Z' or map[z.y + 1][z.x] == 'M' or map[z.y + 1][z.x] == 'N') {
			map[z.y][z.x] = ' ';
			map[z.y + 1][z.x] = 'Z';
			z.y++;
		}
		else if (map[z.y + 1][z.x] == '\'') {
			map[z.y][z.x] = '\'';
			map[z.y + 1][z.x] = 'Z';
			z.y++;
		}
		else {
			z.pos = rand() % 4 + 1;
		}
		break;
	}
	case LEFT: {
		if (map[z.y][z.x - 1] == ' '  or map[z.y][z.x - 1] == 'Z' or map[z.y][z.x - 1] == 'M' or map[z.y][z.x - 1] == 'N') {
			map[z.y][z.x] = ' ';
			map[z.y][z.x - 1] = 'Z';
			z.x--;
		}
		else if (map[z.y][z.x - 1] == '\'') {
			map[z.y][z.x] = '\'';
			map[z.y][z.x - 1] = 'Z';
			z.x--;
		}
		else {
			z.pos = rand() % 4 + 1;
		}
		break;
	}
	}
}

void logic() {
	switch (pacman_motion) {
	case UP: {
		if (map[pacman.y - 1][pacman.x] == ' ' or map[pacman.y - 1][pacman.x] == '\'' or map[pacman.y - 1][pacman.x] == 'Z' or map[pacman.y - 1][pacman.x] == 'M' or map[pacman.y - 1][pacman.x] == 'N') {
			if (map[pacman.y - 1][pacman.x] == 'Z' or map[pacman.y - 1][pacman.x] == 'M' or map[pacman.y - 1][pacman.x] == 'N') {
				deth_by_enemy();
			}
			else if(map[pacman.y - 1][pacman.x] == '\''){
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y - 1][pacman.x] = 'C';
				pacman.y--;
			}
			else {
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y - 1][pacman.x] = 'C';
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
			if (map[pacman.y][pacman.x + 1] == 'Z' or map[pacman.y][pacman.x + 1] == 'M' or map[pacman.y][pacman.x + 1] == 'N') {
				deth_by_enemy();
			}
			else if (map[pacman.y][pacman.x + 1] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y][pacman.x + 1] = 'C';
				pacman.x++;
			}
			else {
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y][pacman.x + 1] = 'C';
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
			if (map[pacman.y + 1][pacman.x] == 'Z' or map[pacman.y + 1][pacman.x] == 'M' or map[pacman.y + 1][pacman.x] == 'N') {
				deth_by_enemy();
			}
			else if (map[pacman.y + 1][pacman.x] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y + 1][pacman.x] = 'C';
				pacman.y++;
			}
			else {
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y + 1][pacman.x] = 'C';
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
			if (map[pacman.y][pacman.x - 1] == 'Z' or map[pacman.y][pacman.x - 1] == 'M' or map[pacman.y][pacman.x - 1] == 'N') {
				deth_by_enemy();
			}
			else if (map[pacman.y][pacman.x - 1] == '\'') {
				score++;
				num_coin--;
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y][pacman.x - 1] = 'C';
				pacman.x--;
			}
			else {
				map[pacman.y][pacman.x] = ' ';
				map[pacman.y][pacman.x - 1] = 'C';
				pacman.x--;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	}
	
	//телепорт на карте
	if (pacman.x == 0 and pacman.y == 10) {
		pacman.x = 24;
		map[10][0] = ' ';
	}
	else if (pacman.x == 24 and pacman.y == 10) {
		pacman.x = 1;
		map[10][24] = ' ';
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

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	setup();
	while (lose == false and win == false) {
		draw_timer_score();
		drawMap();
		input();
		logic();
		enter_monster();
		monster_move();
		spawn_new_fruit();
		win_by_coin();
		system("cls");
	}
	if (win == true) {
		cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tCONGRATULATIONS!!!" << endl;
		cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t   YOU WIN!!!" << endl;
	}
	else if (lose == true) {
		cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tYOU LOSE!" << endl;
	}
	return 0;
}
