#include "Pacman.h"

/*void Pacman::deth_by_monster() {
	if (pacman.y == monsterZ.y and pacman.x == monsterZ.x or
		pacman.y == monsterN.y and pacman.x == monsterN.x or
		pacman.y == monsterM.y and pacman.x == monsterM.x) {
		life--;
		pacman.x = 23;
		pacman.y = 20;
	}
	if (life == 0) lose = true;
}*/

void Pacman::setup_pacman() {
	pacman_motion = STOP;
	this->x = 23;
	this->y = 20;
}

void Pacman::input_move() {
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
		if (map[this->y - 1][this->x] == ' ' or map[this->y - 1][this->x] == '\'' or map[this->y - 1][this->x] == 'Z' or map[this->y - 1][this->x] == 'M' or map[this->y - 1][this->x] == 'N') {
			if (map[this->y][this->x] == '\'') {
				//score++;
				//num_coin--;
				map[this->y][this->x] = ' ';
				this->y--;
			}
			else {
				this->y--;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case RIGHT: {
		if (map[this->y][this->x + 1] == ' ' or map[this->y][this->x + 1] == '\'' or map[this->y][this->x + 1] == 'Z' or map[this->y][this->x + 1] == 'M' or map[this->y][this->x + 1] == 'N') {
			if (map[this->y][this->x] == '\'') {
				//score++;
				//num_coin--;
				map[this->y][this->x] = ' ';
				this->x++;
			}
			else {
				this->x++;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	case DOWN: {
		if (map[this->y + 1][this->x] == ' ' or map[this->y + 1][this->x] == '\'' or map[this->y + 1][this->x] == 'Z' or map[this->y + 1][this->x] == 'M' or map[this->y + 1][this->x] == 'N') {
			if (map[this->y][this->x] == '\'') {
				//score++;
				//num_coin--;
				map[this->y][this->x] = ' ';
				this->y++;
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
		if (map[this->y][this->x - 1] == ' ' or map[this->y][this->x - 1] == '\'' or map[this->y][this->x - 1] == 'Z' or map[this->y][this->x - 1] == 'M' or map[this->y][this->x - 1] == 'N') {
			if (map[this->y][this->x] == '\'') {
				//score++;
				//num_coin--;
				map[this->y][this->x] = ' ';
				this->x--;
			}
			else {
				this->x--;
			}
		}
		else {
			pacman_motion = STOP;
		}
		break;
	}
	}
}

void Pacman::teleport() {
	if (this->x == 0 and this->y == 10) {
		this->x = 24;
		map[10][0] = ' ';
	}
	else if (this->x == 24 and this->y == 10) {
		this->x = 1;
		map[10][24] = ' ';
	}
}