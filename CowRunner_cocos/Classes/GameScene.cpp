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
			ss.flush();
			ss << "apple.png";
			name = "apple";
			sprite = Sprite::create(ss.str());
		break;
		case UnitType::ENEMY:
			ss << "enemy.png";
			name = "enemy";
			sprite = Sprite::create(ss.str());
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
	auto scene = Scene::createWithPhysics();

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

		cow_sprite = BuildSprite(UnitType::COW);
		this->addChild(cow_sprite, LayerType::SPRITES);

		//		auto fruit_sprite = BuildSprite(UnitType::APPLE);
		//		mapLayer->addChild(fruit_sprite, LayerType::SPRITES);

		// creating a keyboard event listener
		listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
			Vec2 cow_pos = event->getCurrentTarget()->getPosition();
			//auto cow_pos = event->getCurrentTarget()
			//auto move = MoveBy::create(2.0, Vec2(cow_pos.x - 10, cow_pos.y));

			switch(keyCode){
				case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				case EventKeyboard::KeyCode::KEY_A:
					std::cout << "Pressed LEFT key\n";
					//event->getCurrentTarget()->setPosition(loc.x, loc.y);
					cow_pos.x -= 50;
					//event->getCurrentTarget()->runAction(move);
					event->getCurrentTarget()->setPosition(cow_pos.x, cow_pos.y);
				break;
				case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				case EventKeyboard::KeyCode::KEY_D:
					std::cout << "Pressed RIGHT key\n";
					cow_pos.x += 50;
					event->getCurrentTarget()->setPosition(cow_pos.x, cow_pos.y);
				break;
				case EventKeyboard::KeyCode::KEY_UP_ARROW:
				case EventKeyboard::KeyCode::KEY_W:
					std::cout << "Pressed UP key\n";
					cow_pos.y += 100;
					event->getCurrentTarget()->setPosition(cow_pos.x, cow_pos.y);
				break;
				case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				case EventKeyboard::KeyCode::KEY_S:
					std::cout << "Pressed DOWN key\n";
					cow_pos.y -= 10;
					event->getCurrentTarget()->setPosition(cow_pos.x, cow_pos.y);
				break;
			}
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cow_sprite);

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
	const float cow_posY = cow_sprite->getPositionY();

	if (cow_posY >= cow_sprite->getContentSize().height / 2) {
		cow_sprite->setPositionY(cow_posY - 1);
	}

	//this->GameLogic();

}
