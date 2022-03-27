#pragma once

#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {

  public:
	  Snake(QWidget *parent = 0);

  protected:
	  void paintEvent(QPaintEvent *);
	  void timerEvent(QTimerEvent *);
	  void keyPressEvent(QKeyEvent *);

  private:
	  QImage head;
	  QImage dot;
	  QImage fruit;

	  // B_WIDTH и B_HEIGHT определяют размеры (ширину и высоту) игрового поля
	  static const int B_WIDTH = 800;
	  static const int B_HEIGHT = 500;
	  // DOT_SIZE — это размеры яблока и «частей» тела змеи
	  static const int DOT_SIZE = 10;
	  // ALL_DOTS определяет максимальное количество возможных точек на доске (900 = (300*300)/(10*10))
	  static const int ALL_DOTS = 4000;
	  // RAND_POS используется для вычисления случайной позиции яблока
	  //static const int RAND_POS = 29;
	  static const int RAND_POS = 51;
	  // DELAY определяет скорость игры
	  static const int DELAY = 140;
	  int delay;
	  int timerId;
	  // длина змеи
	  int dots;
	  int score;
	  int level;
	  int fruits_counter;
	  // позиция яблока
	  int fruit_x;
	  int fruit_y;

	  // координаты частей тела змеи
	  int x[ALL_DOTS];
	  int y[ALL_DOTS];

	  bool leftDirection;
	  bool rightDirection;
	  bool upDirection;
	  bool downDirection;
	  bool inGame;

	  void loadImages();
	  void initGame();
	  void locateFruit();
	  bool isBadFruitLocation();
	  void checkFruit();
	  void checkCollision();
	  void move();
	  void doDrawing();
	  void drawScore(QPainter &);
	  void gameOver(QPainter &);
};
