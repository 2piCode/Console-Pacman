#include "StatusBar.h"

void draw_timer_score_life() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Time: " << hour << " : " << minute << " : " << second;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "\tCollected " << pacman.score_coin << " of 202" << "\tLeft: " << num_coin;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	std::cout << "\tLife: " << pacman.life << std::endl;
}