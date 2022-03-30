#include <ncurses.h>
#include "CowRunner.h"


int main() {
	initscr();                   // Переход в curses-режим

	CowRunner game;

	game.Run();
	endwin();                    // Выход из curses-режима. Обязательная команда.

	return 0;
}
