#include "CowLayer.h"

USING_NS_CC;

Scene* Cow::createScene() {
	return Cow::create();
}

Cow::~Cow() {
	CC_SAFE_DELETE(cow_sprite);
}

void Cow::GameLogic() {

	if (cow_direction == UnitDirection::LEFT) {
		cow_sprite->setFlippedX(true);
	} else {
		cow_sprite->setFlippedX(false);
	}

	if (cow_jump) {
		cow_jump = false;

	}
}

void Cow::initPhysics() {


}

void Cow::update(float dt) {

	this->GameLogic();

}

void Cow::CreateFruit() {

}

// on "init" you need to initialize your instance
bool Cow::init() {

	if ( !Scene::init() ) { // initWithPhysics
		return false;
	}


	cow_direction = UnitDirection::RIGHT;
	cow_state = UnitState::STOP;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// create a sprite
	this->cow_sprite = Sprite::create(); //"cow_stay_1.png");
	cow_sprite->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 2));

	Animation* cow_stay_anim = Animation::create();

	// load image file from local file system to CCSpriteFrame, then add into CCAnimation
	for (int i = 1; i <= 6; ++i) {
		char imageFileName[128];

		sprintf(imageFileName, "cow_stay_%d.png", i);
		cow_stay_anim->addSpriteFrameWithFile(imageFileName);
	}

	cow_stay_anim->setDelayPerUnit(0.2f);// / 6.0f); // This animation contains 14 frames, will     continuous 2.8 seconds.
	cow_stay_anim->setLoops(CC_REPEAT_FOREVER);

	Animate* action = Animate::create(cow_stay_anim);

	cow_sprite->runAction(action);  // run action on sprite object

	// Добавляем в сцену
	this->addChild(cow_sprite, 0);


	// ==================== creating a keyboard event listener =======================
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Cow::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	// Запускаем игровой цикл
	// Как только игровой цикл открывается, он вызывает функцию Cow::update(float dt)
	scheduleUpdate();

	return true;
}


// Implementation of the keyboard event callback function prototype
void Cow::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// log("Key with keycode %d pressed", keyCode);
	// keys: SPACE - ??, UP - 28, DOWN - 29, LEFT - 26, RIGHT - 27, ESC - 6
	switch(keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			cow_direction = UnitDirection::LEFT;
		break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			cow_direction = UnitDirection::RIGHT;
		break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			cow_jump = true;
		break;
		case EventKeyboard::KeyCode::KEY_CTRL:

		break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->pushScene(PauseScene::createScene());
		break;

	}

}


