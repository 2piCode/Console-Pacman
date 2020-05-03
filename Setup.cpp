#include "Setup.h"

void setup() {
	lose = false;
	win = false;

	pacman.setup_pacman();
	monsterZ.setup_monster(monsterZ);
	monsterN.setup_monster(monsterN);
	monsterM.setup_monster(monsterM);
	fruit.setup_spawn_fruit();
	monsterZ.setup_enter_monster_time();
	monsterN.setup_enter_monster_time();
	monsterM.setup_enter_monster_time();
}
