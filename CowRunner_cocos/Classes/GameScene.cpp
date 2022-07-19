#include "GameScene.h"

USING_NS_CC;


GameScene::~GameScene() {
	CC_SAFE_DELETE(mapLayer);
}

TMXTiledMap* GameScene::BuildMapLayer(int level) {
	std::stringstream ss;
	ss << "map_" << level << ".tmx";
	std::cout << ss.str() << '\n';
	// create a map
	return TMXTiledMap::create(ss.str());
}

Sprite* GameScene::BuildSprite(const UnitType type) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* sprite = Sprite::create();
	switch (type) {
		case UnitType::COW:
			sprite->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 2));
		break;
		case UnitType::APPLE:
		case UnitType::ENEMY:
			sprite->setPosition(Vec2(std::rand() % static_cast<int>(visibleSize.height),
															 std::rand() % static_cast<int>(visibleSize.width)));
		break;
	}

	sprite->setScale(objects_scale_XY, objects_scale_XY);
	return sprite;
}

Scene* GameScene::createScene() {

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

	Color4B blueSkyColor(Color3B(184, 237, 255));
	LayerColor* backgroundLayer = LayerColor::create(blueSkyColor);
	this->addChild(backgroundLayer, LayerType::BACKGROUND);

	//mapLayer = BuildMapLayer(currentLevel);
	//this->addChild(mapLayer, LayerType::MAP);
	const Vec2 grass_pos(-15.0, 0);
	const Vec2 grass_anchor(0, 0);
	const std::pair<float, float> sprites_scale = {0.9, 0.9};
	Sprite* grass_back = Sprite::create("res/world/grass_back.png");
	grass_back->setScale(sprites_scale.first, sprites_scale.second);
	grass_back->setAnchorPoint(grass_anchor);
	grass_back->setPosition(grass_pos);
	this->addChild(grass_back, LayerType::BACKGROUND);

	Sprite* grass_front = Sprite::create("res/world/grass_front.png");
	grass_front->setScale(sprites_scale.first, sprites_scale.second);
	grass_front->setAnchorPoint(grass_anchor);
	grass_front->setPosition(grass_pos.x, grass_pos.y - 35);
	this->addChild(grass_front, LayerType::FRONT);

	cow = std::make_shared<GameUnit>("cow");
	cow->setSprite(BuildSprite(UnitType::COW));
	cow->initAnimations();

	this->addChild(cow->getSprite(), LayerType::SPRITES);

	// creating a keyboard event listener
	eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		static_cast<void>(event);
		switch(keyCode) {
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				//std::cout << "Pressed LEFT key\n";
				is_events.isKeyLeft = true;
			break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				//std::cout << "Pressed RIGHT key\n";
				is_events.isKeyRight = true;
			break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
			case EventKeyboard::KeyCode::KEY_W:
				//std::cout << "Pressed UP key\n";
				is_events.isUpKey = true;
			break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			case EventKeyboard::KeyCode::KEY_S:
				//std::cout << "Pressed DOWN key\n";
				is_events.isDownKey = true;
			break;
			case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
				is_events.isShiftKey = true;
			break;
			case EventKeyboard::KeyCode::KEY_SPACE:

			break;
		}
		is_events.is_change_animation = true;
	};

	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		static_cast<void>(event);
		switch(keyCode){
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				//std::cout << "Released LEFT key\n";
				is_events.isKeyLeft = false;
			break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				//std::cout << "Released RIGHT key\n";
				is_events.isKeyRight = false;
			break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
			case EventKeyboard::KeyCode::KEY_W:
				//std::cout << "Released UP key\n";
				is_events.isUpKey = false;
			break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			case EventKeyboard::KeyCode::KEY_S:
				//std::cout << "Released DOWN key\n";
				is_events.isDownKey = false;
			break;
			case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
				is_events.isShiftKey = false;
			break;
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance()->replaceScene(StartMenuScene::createScene());
			break;
			case EventKeyboard::KeyCode::KEY_SPACE:

			break;
		}
		is_events.is_change_animation = true;
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, cow->getSprite());

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


	return true;
}

// Параметр, передаваемый для обновления — это значение, представляющее количество времени в секундах
// с момента последнего вызова функции обновления.
// Поэтому, если с момента последнего вызова обновления прошло 1/10 секунды, переданное значение будет равно 0.1
// В двух словах, при покадровом перемещении выражайте свои единицы в секундах,
// а затем умножайте их на дельту, переданную в функцию обновления.
void GameScene::update(float delta) {
	cow->tick(is_events, delta);

//	auto fruit_sprite = BuildSprite(UnitType::APPLE);
//	mapLayer->addChild(fruit_sprite, LayerType::SPRITES);
//	this->GameLogic();

//	if (is_events.isKeyLeft) {
//		float x, y, z;
//		this->getCamera()->getEye(&x, &y, &z);
//		map->getCamera()->setEye(x-200, y, z+300);
//	}
}
