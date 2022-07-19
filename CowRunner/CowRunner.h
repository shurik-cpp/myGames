#ifndef COWRUNNER_H
#define COWRUNNER_H

#include <random>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <ncurses.h>

class CowRunner {
public:
	explicit CowRunner();

	bool Run();

private:
	enum Direction {
		LEFT,
		RIGHT,
	};

	enum Jump {
		UP,
		DOWN,
		ON_LAND
	};

	enum WhatDrawing {
		COW,
		FRUIT
	};

	struct Cow {
		int pos_x;
		int pos_y;
		Direction dir = RIGHT;
		Jump jump = ON_LAND;
		int fly_counter = 0;

		bool is_run = false;
		bool is_jump = false;
		bool is_legs_out = true;
		const int width = 18;
		const int height = 5;

		const int MAX_HELTH = 100;
		int helth = MAX_HELTH;
		int fat = 0;
		int fat_counter = 0;

		const int MAX_JUMP = 10;
		int jump_height = MAX_JUMP;


		const std::vector<std::string> left_side = {
			"^__^                \n",
			"(oo)\\________       \n",
			"(__)\\        )\\/\\ \n",
			"     ||----w |      \n",
			"     ||     ||      \n"
		};

		const std::vector<std::string> left_run1 = {
			"^__^                \n",
			"(oo)\\________       \n",
			"(__)\\        )\\/\\ \n",
			"     / ----w \\     \n",
			"    //       \\\\   \n"
		};

		const std::vector<std::string> left_run2 = {
			"^__^                \n",
			"(oo)\\________       \n",
			"(__)\\        )\\/\\ \n",
			"     \\ ---w /      \n",
			"      \\\\  //      \n"
		};

		const std::vector<std::string> right_side = {
			"             ^__^  \n",
			"     _______/(oo)  \n",
			" /\\/(       /(__) \n",
			"    | w----||      \n",
			"    ||     ||      \n"
		};

		const std::vector<std::string> right_run1 = {
			"             ^__^  \n",
			"     _______/(oo)  \n",
			" /\\/(       /(__) \n",
			"    / w---- \\     \n",
			"   //       \\\\   \n"
		};

		const std::vector<std::string> right_run2 = {
			"             ^__^  \n",
			"     _______/(oo)  \n",
			" /\\/(       /(__) \n",
			"     \\ w--- /     \n",
			"     \\\\  //      \n"
		};
	};

	struct Fruit {
		int pos_x, pos_y;

		const int show_time = 100;
		int time_counter = 0;

		const std::vector<std::string> apple = {
			" \\  \n",
			"(__) \n"
		};
	};

	int width;
	int height;

	Cow cow;
	Fruit fruit;

	int score = 0;
	int delay = 3;
	bool is_game_run = true;

	void Setup();
	void GenerateNewFruit();
	void DrawImage(const std::vector<std::string>& image, const WhatDrawing& what);
	void Draw();
	void Input();
	void Logic();
	bool Collision();

};

#endif // COWRUNNER_H
