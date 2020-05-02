#include "Fruit.h"

void Fruit::setup_spawn_fruit() {
	this->x = std::rand() % (size_map_x - 3);
	this->y = std::rand() % (size_map_y);
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x); j++) {
			while ((this->y == i and this->x == j and map[i][j] == 'B') or (this->y == i and this->x == j and map[i][j] == 'Z') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*/) {
				this->x = std::rand() % (size_map_x - 3);
				this->y = std::rand() % size_map_y;
			}
		}
	}
}

/*void Fruit::spawn_new_fruit() {
	if (pacman.x == this->x and pacman.y == this->y) {
		this->x = rand() % (size_map_x - 3);
		this->y = rand() % size_map_y;
	}
	for (size_t i = 0; i < size_map_y; i++) {
		for (size_t j = 0; j < (size_map_x); j++) {
			while ((this->y == i and this->x == j and map[i][j] == 'B') or (this->y == i and this->x == j and map[i][j] == '-') /*or (fruit.y == l and fruit.x == n and map[l][n] == ' ')*///) {
	//			this->x = rand() % (size_map_x - 3);
		//		this->y = rand() % size_map_y;
		//	}
		//}
	//}
//}