#include "GameScene.h"

USING_NS_CC;

std::string BuildErrorMsg(const std::string file_name) {
	return "File " + file_name + " not found";
}

GameScene::~GameScene() {
	CC_SAFE_DELETE(mapLayer);
}

TMXTiledMap* GameScene::BuildMapLayer(int level) {
	std::stringstream ss;
	ss << "map_" << level << ".tmx";
	std::cout << ss.str() << '\n';
	// create a map
	auto map = TMXTiledMap::create(ss.str());
	if (map == nullptr) {
		throw std::invalid_argument(BuildErrorMsg(ss.str()));
	}
	return map;
}

Sprite* GameScene::BuildSprite(const UnitType type) {
	Sprite* sprite = nullptr;
	std::stringstream ss; //("'unit-");
	std::string name;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (type) {
		case UnitType::COW:
			ss << "cow_stay_1.png";
			name = "cow_stay_1";
			sprite = Sprite::create(ss.str());
		break;
		case UnitType::APPLE:
//			ss.flush();
//			ss << "apple.png";
//			name = "apple";
//			sprite = Sprite::create(ss.str());
		break;
		case UnitType::ENEMY:
//			ss << "enemy.png";
//			name = "enemy";
//			sprite = Sprite::create(ss.str());
		break;
	}

	if (sprite == nullptr) {
		throw std::invalid_argument(BuildErrorMsg(ss.str()));
	}

	if (type == UnitType::COW) {
		//		auto cow_stay_anim = Animation::create();
		//		// load image file from local file system to CCSpriteFrame, then add into CCAnimation
		//		for (int i = 1; i <= 6; ++i) {
		//			std::stringstream file_name;
		//			file_name << "cow_stay_" << i << ".png";
		//			cow_stay_anim->addSpriteFrameWithFile(file_name.str());
		//		}
		//		cow_stay_anim->setDelayPerUnit(0.2f);
		//		cow_stay_anim->setLoops(CC_REPEAT_FOREVER);

		//		Animate* action = Animate::create(cow_stay_anim);
		//		// run action on sprite object
		//		sprite->runAction(action);

		sprite->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 2));
	}
	else {
		sprite->setPosition(Vec2(std::rand() % static_cast<int>(visibleSize.height),
														 std::rand() % static_cast<int>(visibleSize.width)));
	}

	return sprite;
}


Scene* GameScene::createScene() {

	// create the scene with physics enabled
	auto scene = Scene::create();

	// Создаём слой
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() {

	if ( !Scene::init() ) {
		return false;
	}

	try {
		Color4B blueSkyColor(Color3B(213, 255, 255));
		LayerColor* backgroundLayer = LayerColor::create(blueSkyColor);
		this->addChild(backgroundLayer, LayerType::BACKGROUND);

		mapLayer = BuildMapLayer(currentLevel);
		//this->addChild(mapLayer, LayerType::MAP);

		cow.setSprite(BuildSprite(UnitType::COW));
		this->addChild(cow.getSprite(), LayerType::SPRITES);

		//		auto fruit_sprite = BuildSprite(UnitType::APPLE);
		//		mapLayer->addChild(fruit_sprite, LayerType::SPRITES);

		// creating a keyboard event listener
		eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			switch(keyCode){
				case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				case EventKeyboard::KeyCode::KEY_A:
					std::cout << "Pressed LEFT key\n";
					cow.setDirection(UnitDirection::LEFT);
					isKeyLeft = true;
				break;
				case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				case EventKeyboard::KeyCode::KEY_D:
					std::cout << "Pressed RIGHT key\n";
					cow.setDirection(UnitDirection::RIGHT);
					isKeyRight = true;
				break;
				case EventKeyboard::KeyCode::KEY_UP_ARROW:
				case EventKeyboard::KeyCode::KEY_W:
					std::cout << "Pressed UP key\n";
					if (cow.getJumpStatus() == UnitJumpStatus::ON_LAND) {
						cow.setJumpStatus(UnitJumpStatus::UP);
					}
				break;
				case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				case EventKeyboard::KeyCode::KEY_S:
					std::cout << "Pressed DOWN key\n";
					auto jump_status = cow.getJumpStatus();
					if (jump_status != UnitJumpStatus::DOWN) {
						cow.setJumpStatus(UnitJumpStatus::DOWN);
					}

				break;
			}
		};

		eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			switch(keyCode){
				case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				case EventKeyboard::KeyCode::KEY_A:
					std::cout << "Released LEFT key\n";
					isKeyLeft = false;
				break;
				case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				case EventKeyboard::KeyCode::KEY_D:
					std::cout << "Released RIGHT key\n";
					isKeyRight = false;
				break;
				case EventKeyboard::KeyCode::KEY_UP_ARROW:
				case EventKeyboard::KeyCode::KEY_W:
					std::cout << "Released UP key\n";

				break;
				case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				case EventKeyboard::KeyCode::KEY_S:
					std::cout << "Released DOWN key\n";

				break;
			}
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, cow.getSprite());

		// Запускаем игровой цикл
		// Как только игровой цикл открывается, он вызывает функцию GameScene::update(float dt)
		this->scheduleUpdate();
	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what() << '\n';
		return false;
	}

	return true;
}

void GameScene::update(float delta) {
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	const float gravity = 9.8;

	if ((!isKeyLeft && !isKeyRight)) {
		cow.setState(UnitState::STOP);
	} else {
		cow.setState(UnitState::WALK);
	}

	if (cow.getState() == UnitState::WALK) {
		const float SPEED = 10;
		float cow_speed = 0;
		if (isKeyLeft && isKeyRight) {
			// TODO корова мычит и воспроизводится анимация недовольной коровы (встает на дыбы? :D)
		}	else if (isKeyLeft) {
			cow.getSprite()->setFlippedX(true);
			cow_speed -= SPEED;
		} else if (isKeyRight) {
			cow.getSprite()->setFlippedX(false);
			cow_speed += SPEED;
		}

		cow.getSprite()->setPositionX(cow.getSprite()->getPositionX() + cow_speed);
	}


	const float cow_posY = cow.getSprite()->getPositionY();
	const float MAX_JUMP_ACCELERATION = 20;
	const float ACCEL_DELTA = 0.7;
	static float jump_acceleration = 0;

	if (cow.getJumpStatus() == UnitJumpStatus::UP) {
		jump_acceleration = MAX_JUMP_ACCELERATION;
		cow.setJumpStatus(UnitJumpStatus::FLY);
	}
	else if (cow.getJumpStatus() == UnitJumpStatus::FLY) {
		if (jump_acceleration > 0) {
			cow.getSprite()->setPositionY(cow_posY + jump_acceleration);
			jump_acceleration -= ACCEL_DELTA;
		} else {
			cow.setJumpStatus(UnitJumpStatus::DOWN);
			jump_acceleration = 0;
		}
	}
	else if (cow.getJumpStatus() == UnitJumpStatus::DOWN) {
		if (cow_posY >= cow.getSprite()->getContentSize().height / 2) {
			cow.getSprite()->setPositionY(cow_posY - jump_acceleration);
			if (jump_acceleration < MAX_JUMP_ACCELERATION) {
				jump_acceleration += ACCEL_DELTA;
			}
		}
		else {
			cow.getSprite()->setPositionY(cow.getSprite()->getContentSize().height / 2);
			cow.setJumpStatus(UnitJumpStatus::ON_LAND);
			jump_acceleration = 0;
		}
	}


	//this->GameLogic();

}
