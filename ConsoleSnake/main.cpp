#include <random>
#include <ncurses.h>
#include <cstring>
#include <vector>

class Game {
public:
explicit Game() {
	Setup();
}

void Setup() {
	// Получаем максимально возможное количество строк и столбцов для окна stdscr и записываем эти данные в row и width
	getmaxyx(stdscr, height, width);

	const char* hello_msg = "Snake in console!";
	clear();
	mvwprintw(stdscr, width / 2, (height - strlen(hello_msg)) / 2, "%s", hello_msg);
	refresh();                   // Вывод буфера на настоящий экран
	noecho();             // Выключаем отображение вводимых символов, нужно для getch()
	halfdelay(20);         // Устанавливаем ограничение по времени ожидания getch() в 2 сек, в этот момент ничего не происходит
	getch();    // getch() ожидает нажатие любой клавиши на клавиатуре и возвращает код этой самой клавиши

	snake.pos.resize(snake.new_size);
	const int y = height / 2 - 1;
	for (size_t i = 0; i < snake.pos.size(); ++i) {
		const int x = width / 2 - 1 - i;
		snake.pos[i] = {x, y};
	}

	snake.body.resize(snake.new_size, snake.torso);
	snake.body[0] = snake.head;

	fruit = GetNewFruit();

	dir = STOP;
	score = 0;
	game_over = false;
	delay = 5;
}

bool Run() {
	Input();
	Logic();
	Draw();

	return !game_over;
}

private:
	struct Snake {
		std::vector<std::pair<int, int>> pos;
		std::vector<char> body;
		const char head = '@';
		const char torso = 'o';
		const char fat = 'O';
		const int new_size = 4;
	};

	struct Fruit {
		int pos_x, pos_y;
		static const char f = '*';
	};

	enum Direction {
		STOP,
		LEFT,
		RIGHT,
		UP,
		DOWN
		};

	int width;
	int height;

	Snake snake;
	Fruit fruit;
	Direction dir;
	int score;
	int delay;
	bool game_over;

	Fruit GetNewFruit() {
		return {rand() % width, rand() % (height - 2)};
	}

	void Draw() {
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
		// Получаем максимально возможное количество строк и столбцов для окна stdscr и записываем эти данные в row и width
		getmaxyx(stdscr, height, width);

		// рисуем туловище змеи
		for (size_t i = 1; i < snake.body.size(); ++i) {
			mvwprintw(stdscr, snake.pos[i].second, snake.pos[i].first, "%c", snake.body[i]);
		}
		// рисуем голову змеи, чтобы она всегда была на переднем плане
		mvwprintw(stdscr, snake.pos[0].second, snake.pos[0].first, "%c", snake.head);

		mvwprintw(stdscr, fruit.pos_y, fruit.pos_x, "%c", fruit.f);

		//Выводим информацию о количестве строк и столбцов в левом нижнем углу экрана
		mvwprintw(stdscr, height - 1, 0, "Score: %d; snake_size(): %lu; delay: %i\n", score, snake.body.size(), delay);

		refresh();                   // Вывод буфера на настоящий экран
	}

	void Input() {
		noecho();             // Выключаем отображение вводимых символов, нужно для getch()
		halfdelay(delay);         // Устанавливаем ограничение по времени ожидания getch() в 0.5 сек, в этот момент ничего не происходит
		int key = getch();    // getch() ожидает нажатие любой клавиши на клавиатуре и возвращает код этой самой клавиши

		switch (key){
			case ERR:
				//Если нажатия не было, ничего и не меняем
			break;
			case 'a':
				dir = LEFT;
			break;
			case 'w':
				dir = UP;
			break;
			case 'd':
				dir = RIGHT;
			break;
			case 's':
				dir = DOWN;
			break;
			default:
			break;
		}

	}

	void Logic() {
		if (dir != STOP) {
			for (size_t i = snake.pos.size() - 1; i > 0 ; --i) {
				snake.pos[i] = snake.pos[i - 1];
			}

			for (size_t i = snake.body.size() - 1; i > 0; --i) {
				snake.body[i] = snake.body[i - 1];
				if (snake.body[i] == snake.head) {
					snake.body[i] = snake.torso;
				}
			}
			//snake.body[0] = snake.head;
		}

		int& pos_x = snake.pos[0].first;
		int& pos_y = snake.pos[0].second;

		switch (dir) {
			case LEFT:
				pos_x--;
				if (pos_x < 1) pos_x = width - 1;
			break;
			case RIGHT:
				pos_x++;
				if (pos_x > width - 1) pos_x = 1;
			break;
			case UP:
				pos_y--;
				if (pos_y < 0) pos_y = height - 2;
			break;
			case DOWN:
				pos_y++;
				if (pos_y > height - 2) pos_y = 0;
			break;
			case STOP:
			break;
		}

		if (CheckFruit()) {
			snake.pos.push_back({fruit.pos_x, fruit.pos_y});
			snake.body.push_back(snake.torso);
			snake.body[1] = snake.fat;
			fruit = GetNewFruit();
			score++;

			if (delay > 0 && !(score % 5)) {
				delay--;
			}
		}
	}

	bool CheckFruit() {
		if (snake.pos[0].first == fruit.pos_x
				&& snake.pos[0].second == fruit.pos_y) {
			return true;
		}
		return false;
	}

};

int main() {
	initscr();                   // Переход в curses-режим

	Game game;
	while (game.Run()) {}

	endwin();                    // Выход из curses-режима. Обязательная команда.

	return 0;
}
