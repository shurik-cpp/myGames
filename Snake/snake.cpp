#include "snake.h"

#include <QPainter>
#include <QTime>


Snake::Snake(QWidget *parent) : QWidget(parent) {

	setStyleSheet("background-color:black;");
	leftDirection = false;
	rightDirection = true;
	upDirection = false;
	downDirection = false;
	inGame = true;

	resize(B_WIDTH, B_HEIGHT);
	loadImages();
	initGame();
}

void Snake::loadImages() {

	dot.load("dot.png");
	head.load("head.png");
	fruit.load("fruit.png");
}

void Snake::initGame() {

	dots = 5;
	score = 0;
	level = 0;

	for (int z = 0; z < dots; z++) {
		x[z] = 50 - z * 10;
		y[z] = 50;
	}

	locateFruit();
	delay = DELAY;
	timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doDrawing();
}

void Snake::doDrawing() {

	QPainter qp(this);

	if (inGame) {
		qp.drawImage(fruit_x, fruit_y, fruit);

		for (int z = 0; z < dots; z++) {
			if (z == 0) {
				qp.drawImage(x[z], y[z], head);
			} else {
				qp.drawImage(x[z], y[z], dot);
			}
		}

	} else {

		gameOver(qp);
	}
	drawScore(qp);
}

void Snake::drawScore(QPainter &qp) {
	QString score_str, lvl_str;
	score_str.setNum(score);
	lvl_str.setNum(level);
	QString scr = "Score: " + score_str;
	QString lvl = "Level: " + lvl_str;
	QFont font("Courier", 10);

	QFontMetrics fm(font);
	int lvlWidth = fm.width(lvl);

	qp.setPen(QColor(Qt::white));
	qp.setFont(font);

	//qp.translate(QPoint(0, 8));
	qp.drawText(0, 9, scr);
	qp.drawText(B_WIDTH - lvlWidth, 9, lvl);
}

void Snake::gameOver(QPainter &qp) {

	QString message = "Game over";
	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width(message);

	qp.setPen(QColor(Qt::white));
	qp.setFont(font);
	int h = height();
	int w = width();

	qp.translate(QPoint(w/2, h/2));
	qp.drawText(-textWidth/2, 0, message);
}

void Snake::checkFruit() {

	if ((x[0] == fruit_x) && (y[0] == fruit_y)) {
		score++;
		fruits_counter++;
		if (fruits_counter == 10) {
			delay -= 10;
			killTimer(timerId);
			timerId = startTimer(delay);
			fruits_counter = 0;
			level++;

		}
		dots++;
		locateFruit();
	}
}

void Snake::move() {

	for (int z = dots; z > 0; z--) {
		x[z] = x[(z - 1)];
		y[z] = y[(z - 1)];
	}

	if (leftDirection) {
		x[0] -= DOT_SIZE;
		//x[0]--;
	}

	if (rightDirection) {
		x[0] += DOT_SIZE;
		//x[0]++;
	}

	if (upDirection) {
		y[0] -= DOT_SIZE;
		//y[0]--;
	}

	if (downDirection) {
		y[0] += DOT_SIZE;
		//y[0]++;
	}
}

void Snake::checkCollision() {

//	for (int z = dots; z > 0; z--) {

//		if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
//			inGame = false;
//		}
//	}

	if (y[0] >= B_HEIGHT) {
		//inGame = false;
		y[0] = 0;
	}

	if (y[0] < 0) {
		//inGame = false;
		y[0] = B_HEIGHT;
	}

	if (x[0] >= B_WIDTH) {
		//inGame = false;
		x[0] = 0;
	}

	if (x[0] < 0) {
		//inGame = false;
		x[0] = B_WIDTH;
	}

	if(!inGame) {
		killTimer(timerId);
	}
}

void Snake::locateFruit() {

	QTime time = QTime::currentTime();
	qsrand((uint) time.msec());

	int r = qrand() % RAND_POS;
	fruit_x = (r * DOT_SIZE);

	r = qrand() % RAND_POS;
	fruit_y = (r * DOT_SIZE);

	if (isBadFruitLocation()) {
		locateFruit();
	}

}

bool Snake::isBadFruitLocation() {
	if (fruit_x >= B_WIDTH || fruit_y >= B_HEIGHT || fruit_x <= 0 || fruit_y <= 0) {
		return true;
	}
	for (int z = 0; z < dots; ++z) {
		if (fruit_x == x[z] && fruit_y == y[z]) {
			return true;
		}
	}
	return false;
}

void Snake::timerEvent(QTimerEvent *e) {

	Q_UNUSED(e);

	if (inGame) {

		checkFruit();
		checkCollision();
		move();
	}

	repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

	int key = e->key();

	if ((key == Qt::Key_Left) && (!rightDirection)) {
		leftDirection = true;
		upDirection = false;
		downDirection = false;
	}

	if ((key == Qt::Key_Right) && (!leftDirection)) {
		rightDirection = true;
		upDirection = false;
		downDirection = false;
	}

	if ((key == Qt::Key_Up) && (!downDirection)) {
		upDirection = true;
		rightDirection = false;
		leftDirection = false;
	}

	if ((key == Qt::Key_Down) && (!upDirection)) {
		downDirection = true;
		rightDirection = false;
		leftDirection = false;
	}

	if (key == Qt::Key_Enter) {
		inGame = !inGame;
	}

	QWidget::keyPressEvent(e);
}
