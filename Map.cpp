#include "Map.h"

void draw_map() {
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			if (map[i][j] == '|') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << "|";
			}
			else if (map[i][j] == '-') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << "-";
			}
			else if (i == monsterZ.y and j == monsterZ.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				std::cout << "Z";
			}
			else if (i == monsterN.y and j == monsterN.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				std::cout << "N";
			}
			else if (i == monsterM.y and j == monsterM.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				std::cout << "M";
			}
			else if (i == fruit.y and j == fruit.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
				std::cout << '0';
			}
			else if (i == pacman.y and j == pacman.x) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "C";
			}
			else if (map[i][j] == '\'') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << '\'';
			}
			else if (map[i][j] == '-') {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
				std::cout << "-";
			}
			else if (map[i][j] == ' ') {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}