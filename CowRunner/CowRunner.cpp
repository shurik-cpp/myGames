#include "CowRunner.h"

CowRunner::CowRunner() {
	Setup();
}

bool CowRunner::Run() {
	while (is_game_run) {
		Input();
		Logic();
		Draw();
	}

	std::string msg = "Game over!";
	mvwprintw(stdscr, height / 2 - 2, (width - msg.size()) / 2, "%s\n", msg.c_str());
	std::stringstream end_score;
	end_score << "Score: " << score;
	msg = end_score.str();
	mvwprintw(stdscr, height / 2, (width - msg.size()) / 2, "%s\n", msg.c_str());
	refresh();                   // Вывод буфера на настоящий экран

	while (true) {
		if (getch() > ERR){
			break;
		}
	}

	return false;
}

void CowRunner::Setup() {
	// Получаем максимально возможное количество строк и столбцов для окна stdscr и записываем эти данные в row и width
	getmaxyx(stdscr, height, width);

	cow.pos_x = cow.width;
	cow.pos_y = height - 1 - cow.height ;

	GenerateNewFruit();

	score = 0;
	is_game_run = true;
	delay = 1;
}

void CowRunner::GenerateNewFruit() {
	fruit.pos_x = rand() % (width - 4);
	fruit.pos_y = rand() % (height - 4);
}

void CowRunner::DrawImage(const std::vector<std::string>& image, const WhatDrawing& what) {
	int line = 0;
	for (const auto& it : image) {
		switch (what) {
			case COW:
				mvwprintw(stdscr, cow.pos_y + line, cow.pos_x, "%s", it.c_str());
			break;
			case FRUIT:
				mvwprintw(stdscr, fruit.pos_y + line, fruit.pos_x, "%s", it.c_str());
			break;
		}

		line++;
	}
}

void CowRunner::Draw() {
	// Все функции вывода условно можно поделить на три группы:

	// addch()-функции. Вывод одного символа с заданными атрибутами.
	// printw()-функции. Форматированный вывод.
	// addstr()-функции. Вывод строки.
	/// https://code-live.ru/post/ncurses-input-output/
	//
	// printw()-функции
	// Эти функции практически полностью аналогичны функции printf(). http://www.c-cpp.ru/content/printf
	// Только у printw(), как у любой уважающей себя ncurses-функции, есть модификации
	// для форматированного вывода на окно — wprintw(),
	// вывод, начиная с определённых координат — mvprintw(),
	// вывод на окно, начиная с определённых координат — mvwprintw().

	clear();

	WhatDrawing what = FRUIT;
	DrawImage(fruit.apple, what);

	// рисуем корову:
	what = COW;
	switch (cow.dir) {
		case LEFT:
			if (cow.is_jump) {
				DrawImage(cow.left_run1, what);
			}
			else if (cow.is_run) {
				if (cow.is_legs_out) {
					DrawImage(cow.left_run1, what);
				} else {
					DrawImage(cow.left_run2, what);
				}
			}
			else {
				DrawImage(cow.left_side, what);
			}
		break;
		case RIGHT:
			if (cow.is_jump) {
				DrawImage(cow.right_run1, what);
			}
			else if (cow.is_run) {
				if (cow.is_legs_out) {
					DrawImage(cow.right_run1, what);
				} else {
					DrawImage(cow.right_run2, what);
				}
			}
			else {
				DrawImage(cow.right_side, what);
			}
		break;
	}
	//Выводим информацию в левом нижнем углу экрана
	mvwprintw(stdscr, height - 1, 0, "Helth: %d; Fat: %d; Score: %d\n", cow.helth, cow.fat, score);


	refresh();                   // Вывод буфера на настоящий экран
}

void CowRunner::Input() {
	noecho();             // Выключаем отображение вводимых символов, нужно для getch()
	halfdelay(delay);     // Устанавливаем ограничение по времени ожидания getch() в 0.5 сек, в этот момент ничего не происходит
	int key = getch();    // getch() ожидает нажатие любой клавиши на клавиатуре и возвращает код этой самой клавиши

	switch (key){
		case ERR:
			//Если нажатия не было
			//cow.is_run = false;
		break;
		case 68: //'a':
			cow.dir = LEFT;
			cow.is_run = true;
		break;
		case 65: //'w':
			if (!cow.is_jump){
				cow.is_jump = true;
				cow.jump = UP;
				cow.fly_counter = 0;
			}
		break;
		case 67: //'d':
			cow.dir = RIGHT;
			cow.is_run = true;
		break;
		case 66: //'s':
			cow.jump = DOWN;
			cow.is_run = false;
		break;
		default:

		break;
	}
}

void CowRunner::Logic() {
	// Получаем максимально возможное количество строк и столбцов для окна stdscr и записываем эти данные в row и width
	getmaxyx(stdscr, height, width);

	switch (cow.dir) {
		case LEFT:
			if (cow.is_run) {
				cow.is_legs_out = !cow.is_legs_out;
				cow.pos_x--;
				if (cow.pos_x < 1) {
					cow.pos_x = 1;
					cow.is_run = false;
				}
			}
		break;
		case RIGHT:
			if (cow.is_run) {
				cow.is_legs_out = !cow.is_legs_out;
				cow.pos_x++;
				if (cow.pos_x > width - cow.width) {
					cow.pos_x = width - cow.width;
					cow.is_run = false;
				}
			}
		break;
	}
	switch (cow.jump) {
		case UP:
			cow.pos_y--;
			if (cow.pos_y < 0) cow.pos_y = 0;
			cow.fly_counter++;
			if (cow.fly_counter > cow.jump_height) {
				cow.jump = DOWN;
			}
		break;
		case DOWN:
			cow.pos_y++;
			if (cow.pos_y > (height - 1 - cow.height)) {
				cow.pos_y = (height - 1) - cow.height;
				cow.jump = ON_LAND;
				cow.is_jump = false;
			}
		break;
		case ON_LAND:

		break;
	}

	if (Collision()) {
		if (cow.is_run || cow.is_jump) {
			score++;
			if (cow.helth < cow.MAX_HELTH) {
				cow.helth++;
			}
		} else {
			cow.fat++;
			cow.helth += 50;
			if (cow.helth > cow.MAX_HELTH) {
				cow.helth = cow.MAX_HELTH;
			}
		}
		GenerateNewFruit();
		fruit.time_counter = 0;
	}
	else {
		fruit.time_counter++;
		if (fruit.time_counter >= fruit.show_time) {
			if (cow.is_run || cow.is_jump) cow.helth -= 10;
			else cow.helth--;

			if (cow.is_run || cow.is_jump) cow.fat -= 5;
			else cow.fat--;
			if (cow.fat < 0) cow.fat = 0;

			cow.fat_counter++;
			GenerateNewFruit();
			fruit.time_counter = 0;
		}
	}
	if (cow.helth <= 0) {
		is_game_run = false;
	}
	cow.jump_height = cow.MAX_JUMP - cow.fat;
}

bool CowRunner::Collision() {
	bool is_check_x = false;
	bool is_check_y = false;
	for (int i = 0; i < cow.width; ++i) {
		if (cow.pos_x + i == fruit.pos_x + 1) {
			is_check_x = true;
		}
	}
	for (int i = 0; i < cow.height; ++i) {
		if (cow.pos_y + i == fruit.pos_y + 1) {
			is_check_y = true;
		}
	}
	return is_check_x && is_check_y;
}
