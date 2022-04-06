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
			ss << "res/cow/cow_stay_1.png";
			name = "cow_stay_1";
			sprite = Sprite::create();
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
		auto cow_frame_cache = SpriteFrameCache::getInstance();// кеш загружен в AppDeligate.cpp ( spritecache->addSpriteFramesWithFile("res/cow/cow_stay_sheet.plist"); )

		Animation* cow_stay_anim = Animation::create();
		for (int i = 1; i <= 13; i++) {
			std::stringstream file_name;
			file_name << "./cow_stay_" << i;
			//std::cout << file_name.str() << std::endl;
			cow_stay_anim->addSpriteFrame(cow_frame_cache->getSpriteFrameByName(file_name.str()));
		}

		cow_stay_anim->setDelayPerUnit(0.08f);// / 6.0f); // This animation contains 14 frames, will     continuous 2.8 seconds.
		cow_stay_anim->setLoops(CC_REPEAT_FOREVER);

		Animate* action = Animate::create(cow_stay_anim);

		// run action on sprite object
		sprite->runAction(action);

		sprite->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 2));
	}
	else {
		sprite->setPosition(Vec2(std::rand() % static_cast<int>(visibleSize.height),
														 std::rand() % static_cast<int>(visibleSize.width)));
	}
	sprite->setScale(0.9, 0.9);
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
		//Color4B blueSkyColor(Color3B(213, 255, 255));
		Color4B blueSkyColor(Color3B(184, 237, 255));
		LayerColor* backgroundLayer = LayerColor::create(blueSkyColor);
		this->addChild(backgroundLayer, LayerType::BACKGROUND);

		//mapLayer = BuildMapLayer(currentLevel);
		//this->addChild(mapLayer, LayerType::MAP);
		const Vec2 grass_pos(-50, 0);
		const Vec2 grass_anchor(0, 0);
		const std::pair<float, float> sprites_scale = {0.3, 0.3};
		Sprite* grass_back = Sprite::create("res/world/grass_back.png");
		grass_back->setScale(sprites_scale.first, sprites_scale.second);
		grass_back->setAnchorPoint(grass_anchor);
		grass_back->setPosition(grass_pos);
		this->addChild(grass_back, LayerType::BACKGROUND);

		Sprite* grass_front = Sprite::create("res/world/grass_front.png");
		grass_front->setScale(sprites_scale.first, sprites_scale.second);
		grass_front->setAnchorPoint(grass_anchor);
		grass_front->setPosition(grass_pos);
		this->addChild(grass_front, LayerType::FRONT);

		cow.setSprite(BuildSprite(UnitType::COW));
		this->addChild(cow.getSprite(), LayerType::SPRITES);

		//		auto fruit_sprite = BuildSprite(UnitType::APPLE);
		//		mapLayer->addChild(fruit_sprite, LayerType::SPRITES);

		// creating a keyboard event listener
		eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			static_cast<void>(event);
			switch(keyCode) {
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
					isUpKey = true;
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
			static_cast<void>(event);
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
					isUpKey = false;
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
		// у нас есть контроль над приоритетом, с которым программа обновления будет просматривать нашу функцию обновления.
		// По умолчанию, когда мы вызываем scheduleUpdate(), наша функция обновления будет вызываться для каждого кадра.
		// Если узел, который мы обновляем, не нужно обновлять каждый кадр, мы просто тратим впустую мощность процессора
		// (и время автономной работы). Если есть обновление с более низким приоритетом, мы можем использовать:
		// this->scheduleUpdateWithPriority(42);
		// Сначала вызывает все update(), для которых не установлен приоритет. Затем вызовет узел с наименьшим значением,
		// затем следующий с наибольшим и т.д.
		// (https://gamefromscratch.com/cocos2d-x-tutorial-series-game-loop-updates-and-action-handling/)
		this->scheduleUpdate();
	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what() << '\n';
		return false;
	}

	return true;
}

// Параметр, передаваемый для обновления — это значение, представляющее количество времени в секундах
// с момента последнего вызова функции обновления.
// Поэтому, если с момента последнего вызова обновления прошло 1/10 секунды, переданное значение будет равно 0.1
// В двух словах, при покадровом перемещении выражайте свои единицы в секундах,
// а затем умножайте их на дельту, переданную в функцию обновления.
void GameScene::update(float delta) {
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	const float gravity = 9.8;

	if ((!isKeyLeft && !isKeyRight)) {
		cow.setState(UnitState::STOP);
	} else {
		cow.setState(UnitState::WALK);
	}

	if (cow.getState() == UnitState::WALK) {
		const float SPEED = 350 * delta;
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
	const float MAX_JUMP_ACCELERATION = 1000 * delta;
	const float JUMP_DELTA = 30 * delta;
	const float COW_ON_LAND_Y = 125;
	static float jump_acceleration = 0;

	if (cow.getJumpStatus() == UnitJumpStatus::ON_LAND) {
		if (isUpKey) {
			cow.setJumpStatus(UnitJumpStatus::UP);
		}
	}

	if (cow.getJumpStatus() == UnitJumpStatus::UP) {
		jump_acceleration = MAX_JUMP_ACCELERATION;
		cow.setJumpStatus(UnitJumpStatus::FLY);
	}
	else if (cow.getJumpStatus() == UnitJumpStatus::FLY) {
		if (jump_acceleration > 0) {
			cow.getSprite()->setPositionY(cow_posY + jump_acceleration);
			jump_acceleration -= JUMP_DELTA;
		} else {
			cow.setJumpStatus(UnitJumpStatus::DOWN);
			jump_acceleration = 0;
		}
	}
	else if (cow.getJumpStatus() == UnitJumpStatus::DOWN) {
		if (cow_posY >= COW_ON_LAND_Y) {
			cow.getSprite()->setPositionY(cow_posY - jump_acceleration);
			if (jump_acceleration < MAX_JUMP_ACCELERATION) {
				jump_acceleration += JUMP_DELTA;
			}
		}
		else {
			cow.getSprite()->setPositionY(COW_ON_LAND_Y);
			cow.setJumpStatus(UnitJumpStatus::ON_LAND);
			jump_acceleration = 0;
		}
	}


	//this->GameLogic();

}
