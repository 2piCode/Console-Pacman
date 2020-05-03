#include "StatusBar.h"

void draw_timer_score_life() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	game.hour = timeinfo->tm_hour;
	game.minute = timeinfo->tm_min;
	game.second = timeinfo->tm_sec;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Time: " << game.hour << " : " << game.minute << " : " << game.second;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "\tCollected " << pacman.score_coin << " of 202" << "\tLeft: " << game.num_coin;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	std::cout << "\tLife: " << pacman.life << std::endl;
}