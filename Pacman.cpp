#include "Pacman.h"

void Pacman::deth_by_monster() {
	if (this->y == monsterZ.y and this->x == monsterZ.x or
		this->y == monsterN.y and this->x == monsterN.x or
		this->y == monsterM.y and this->x == monsterM.x) {
		life--;
		this->x = 23;
		this->y = 20;
	}
	if (life == 0) game.lose = true;
}

void Pacman::setup_pacman() {
	pacman_motion = STOP;
	this->x = 23;
	this->y = 20;
}

void Pacman::input_move() {
	while (_kbhit()) {
		switch (_getch()) {
		case 'w': {
			pacman_motion = UP;
			break;
		}
		case 'W': {
			pacman_motion = UP;
			break;
		}
		case KEY_UP: {
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
		case KEY_RIGHT: {
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
		case KEY_DOWN: {
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
		case KEY_LEFT: {
			pacman_motion = LEFT;
			break;
		}
		}
	}
}

void Pacman::pacman_move() {
	switch (pacman_motion) {
	case UP: {
		if (board.map[this->y - 1][this->x] == ' ' or board.map[this->y - 1][this->x] == '\'' or board.map[this->y - 1][this->x] == 'Z' or board.map[this->y - 1][this->x] == 'M' or board.map[this->y - 1][this->x] == 'N') {
			if (board.map[this->y][this->x] == '\'') {
				board.collected_coin_UP();
			}else {
				this->y--;
			}
		}else {
			pacman_motion = STOP;
		}
		break;
	}
	case RIGHT: {
		if (board.map[this->y][this->x + 1] == ' ' or board.map[this->y][this->x + 1] == '\'' or board.map[this->y][this->x + 1] == 'Z' or board.map[this->y][this->x + 1] == 'M' or board.map[this->y][this->x + 1] == 'N') {
			if (board.map[this->y][this->x] == '\'') {
				board.collected_coin_RIGHT();
			}else {
				this->x++;
			}
		}else {
			pacman_motion = STOP;
		}
		break;
	}
	case DOWN: {
		if (board.map[this->y + 1][this->x] == ' ' or board.map[this->y + 1][this->x] == '\'' or board.map[this->y + 1][this->x] == 'Z' or board.map[this->y + 1][this->x] == 'M' or board.map[this->y + 1][this->x] == 'N') {
			if (board.map[this->y][this->x] == '\'') {
				board.collected_coin_DOWN();
			}
			else {
				this->y++;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case LEFT: {
		if (board.map[this->y][this->x - 1] == ' ' or board.map[this->y][this->x - 1] == '\'' or board.map[this->y][this->x - 1] == 'Z' or board.map[this->y][this->x - 1] == 'M' or board.map[this->y][this->x - 1] == 'N') {
			if (board.map[this->y][this->x] == '\'') {
				board.collected_coin_LEFT();
			}else {
				this->x--;
			}
		}else {
			pacman_motion = STOP;
		}
		break;
	}
	}
}

void Pacman::teleport() {
	if (this->x == 0 and this->y == 10) {
		this->x = 24;
		board.map[10][0] = ' ';
	}
	else if (this->x == 24 and this->y == 10) {
		this->x = 1;
		board.map[10][24] = ' ';
	}
}