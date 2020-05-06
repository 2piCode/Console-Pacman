#include "GameClass.h"

void GameClass::win_by_coin() {
	if (this->num_coin == 0) this->win = true;
}

void GameClass::win_game() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\t\tCONGRATULATIONS!!!" << std::endl;
	std::cout << "\t\t\t\t\t\t   YOU WIN!!!" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
}

void GameClass::lose_game() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\t\t    YOU LOSE!" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
}

void GameClass::hello() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\tWelcome to the Pacman console game" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
}

void GameClass::goodbye() {
	system("cls");
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\t\tSEE YOU LATER" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
}

void GameClass::author() {
	setcur(0, 0);
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t||===========================================||" << std::endl;
	std::cout << "\t\t\t\t\t\t   AUTHOR" << std::endl;
	std::cout << "\t\t\t\t||===========================================||" << std::endl;
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	std::cout << "\t\t\t\t\t\tIVAN TUPIKOV" << std::endl;
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND | COLOR_3DFACE);
	std::cout << "PRESS ESCAPE TO EXIT";
}

void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
