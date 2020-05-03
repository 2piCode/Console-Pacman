#include "Menu.h"

void Menu::set_name() {
	menu.name[0] = (char*)"PLAY";
	menu.name[1] = (char*)"AUTHOR";
	menu.name[2] = (char*)"EXIT";
}

void Menu::set_name_end() {
	menu.name[0] = (char*)"RETRY";
	menu.name[1] = (char*)"AUTHOR";
	menu.name[2] = (char*)"EXIT";
}

void Menu::active_item() {
	if (GetAsyncKeyState(VK_UP)){
		if (menu.active == 0)
		{
			menu.active = menu.item;
			return;
		}
		menu.active--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (menu.active == menu.item)
		{
			menu.active = 1;
			return;
		}
		menu.active++;
	}
}

void Menu::draw_menu() {
	menu.set_name();

	while (!GetAsyncKeyState(VK_RETURN)) {
		setcur(0, 0);
		game.hello();
		std::cout << std::endl;
		for (size_t i = 0; i < menu.item; i++) {
			if (i == menu.active) {
				std::cout << "| -> " << menu.name[i] << std::endl;
			}
			else {
				std::cout << "|    " << menu.name[i] << std::endl;
			}
		}
		menu.active_item();
		Sleep(30);
	}
}

void Menu::draw_menu_end(bool win) {
	menu.set_name_end();
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	while (!GetAsyncKeyState(VK_RETURN)) {
		setcur(0, 0);
		if (win == true) game.win_game();
		else game.lose_game();
		std::cout << std::endl;
		for (size_t i = 0; i < menu.item; i++) {
			if (i == menu.active) {
				std::cout << "| -> " << menu.name[i] << std::endl;
			}
			else {
				std::cout << "|    " << menu.name[i] << std::endl;
			}
		}
		menu.active_item();
		Sleep(100);
	}
}

void Menu::check_active() {
	if (this->active == 0) {
		game.win = false;
		game.lose = false;
		game.num_coin = 202;
		pacman.score_coin = 0;
		pacman.life = 3;
		monsterZ.side_move = 5;
		monsterN.side_move = 5;
		monsterM.side_move = 5;
	}
	if (this->active == 2) {
		game.goodbye();
		exit(1);
	}
	while (this->active == 1) {
		while (!GetAsyncKeyState(VK_ESCAPE)) game.author();
		system("cls");
		menu.draw_menu();
	}
}