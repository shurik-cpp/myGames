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
	shapeCache->createBodyWithName("ground");
	return map;
}

Sprite* GameScene::BuildSprite(const UnitType type) {
	Sprite* sprite = nullptr;
	std::stringstream ss; //("'unit-");
	std::string name;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (type) {
		case UnitType::COW:
			ss << "collection-cartoon-cow-images-2.png";
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

	// attach physics body
	shapeCache->setBodyOnSprite(name, sprite);

	return sprite;
}

void GameScene::update(float dt) {

	//this->GameLogic();

}

Scene* GameScene::createScene() {

	// create the scene with physics enabled
	auto scene = Scene::createWithPhysics();

	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -9.8));

	// optional: set debug draw
	scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

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
		// Load shapes
		shapeCache = PhysicsShapeCache::getInstance();
		shapeCache->addShapesWithFile("physics.plist");


		LayerColor* blueSky = LayerColor::create(Color4B::BLUE);
		this->addChild(blueSky, LayerType::BACKGROUND);

		mapLayer = BuildMapLayer(currentLevel);
		this->addChild(mapLayer, LayerType::MAP);

		cow_sprite = BuildSprite(UnitType::COW);
		mapLayer->addChild(cow_sprite, LayerType::SPRITES);



//		auto fruit_sprite = BuildSprite(UnitType::APPLE);
//		mapLayer->addChild(fruit_sprite, LayerType::SPRITES);

	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what() << '\n';
		return false;
	}

	// Запускаем игровой цикл
	// Как только игровой цикл открывается, он вызывает функцию GameScene::update(float dt)
	this->scheduleUpdate();

	return true;
}


