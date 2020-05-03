#include "Monster.h"

void Monster::setup_monster(Monster& enemy) {
	if (&enemy == &monsterZ) {
		enemy.x = 11;
		enemy.y = 10;
	}
	else if (&enemy == &monsterN) {
		enemy.x = 12;
		enemy.y = 10;
	}
	else if (&enemy == &monsterM) {
		enemy.x = 13;
		enemy.y = 10;
	}

}

void Monster::setup_enter_monster_time() {
	time_t rawtime = time(NULL);

	struct tm* timeinfo = localtime(&rawtime);
	int stopwatch_enter_monster_min;
	stopwatch_enter_monster_sec = timeinfo->tm_sec;
	stopwatch_enter_monster_min = timeinfo->tm_min;
	stopwatch_enter_monster_sec += stopwatch_enter_monster_min * 60;
}

void Monster::monster_enter() {
	if (stopwatch_enter_monster_sec == game.second + game.minute * 60 - 5 and this->y == 10 and this->x == 11) {
		this->x = 12;
		this->y = 8;
		this->side_move = std::rand() % 4 + 1;
		board.map[8][11] = ' ';
	}
	else if (stopwatch_enter_monster_sec == game.second + game.minute * 60 - 10 and this->y == 10 and this->x == 12) {
		this->x = 12;
		this->y = 8;
		this->side_move = std::rand() % 4 + 1;
		board.map[8][11] = ' ';
	}
	else if (stopwatch_enter_monster_sec == game.second + game.minute * 60 - 20 and this->y == 10 and this->x == 13) {
		this->x = 12;
		this->y = 8;
		this->side_move = std::rand() % 4 + 1;
		board.map[8][11] = ' ';
	}
}

void Monster::monster_move() {
	switch (this->side_move) {
	case 1: {
		if (board.map[this->y - 1][this->x] == ' ' or board.map[this->y - 1][this->x] == '\'') {
			this->y--;

		}
		else {
			this->side_move = rand() % 4 + 1;
		}
		break;
	}
	case 2: {
		if (board.map[this->y][this->x + 1] == ' ' or board.map[this->y][this->x + 1] == '\'') {
			this->x++;
		}
		else {
			this->side_move = rand() % 4 + 1;
		}
		break;
	}
	case 3: {
		if (board.map[this->y + 1][this->x] == ' ' or board.map[this->y + 1][this->x] == '\'') {
			this->y++;
		}
		else {
			this->side_move = rand() % 4 + 1;
		}
		break;
	}
	case 4: {
		if (board.map[this->y][this->x - 1] == ' ' or board.map[this->y][this->x - 1] == '\'') {
			this->x--;
		}
		else {
			this->side_move = rand() % 4 + 1;
		}
		break;
	}
	}
}

void Monster::teleport() {
	if (this->x == 0 and this->y == 10) {
		this->x = 24;
		board.map[10][0] = ' ';
	}
	else if (this->x == 24 and this->y == 10) {
		this->x = 1;
		board.map[10][24] = ' ';
	}
}

void Monster::all_monster_enter() {
	monsterZ.monster_enter();
	monsterN.monster_enter();
	monsterM.monster_enter();
}

void Monster::all_monster_move() {
	monsterZ.monster_move();
	monsterN.monster_move();
	monsterM.monster_move();
}

void Monster::all_monster_teleport() {
	monsterZ.teleport();
	monsterN.teleport();
	monsterM.teleport();
}