#include "Map.h"

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

void Map::draw_map() {
	ShowConsoleCursor(FALSE);
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

void Map::collected_coin_UP() {
	pacman.score_coin++;
	game.num_coin--;
	this->map[pacman.y][pacman.x] = ' ';
	pacman.y--;
}

void Map::collected_coin_DOWN() {
	pacman.score_coin++;
	game.num_coin--;
	this->map[pacman.y][pacman.x] = ' ';
	pacman.y++;
}

void Map::collected_coin_LEFT() {
	pacman.score_coin++;
	game.num_coin--;
	this->map[pacman.y][pacman.x] = ' ';
	pacman.x--;
}

void Map::collected_coin_RIGHT() {
	pacman.score_coin++;
	game.num_coin--;
	this->map[pacman.y][pacman.x] = ' ';
	pacman.x++;
}

void Map::update_map() {
	char newMap[size_map_y][size_map_x]{
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
	for(size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < size_map_x; j++) {
			this->map[i][j] = newMap[i][j];
		}
	}
}