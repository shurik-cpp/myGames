#include "GameScene.h"



USING_NS_CC;


std::string BuildErrorMsg(const std::string file_name) {
	return "File " + file_name + " not found";
}

Scene* GameScene::createScene() {
	return GameScene::create();
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
	std::stringstream ss("'unit-");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (type) {
		case UnitType::COW:
			ss << "cow'.png";
			sprite = Sprite::create();
		break;
		case UnitType::APPLE:
			ss.flush();
			ss << "apple.png";
			sprite = Sprite::create("apple.png");
		break;
		case UnitType::ENEMY:
			ss << "enemy'.png";
			sprite = Sprite::create();
		break;
	}

	if (sprite == nullptr) {
		throw std::invalid_argument(BuildErrorMsg(ss.str()));
	}

	if (type == UnitType::COW) {
		auto cow_stay_anim = Animation::create();
		// load image file from local file system to CCSpriteFrame, then add into CCAnimation
		for (int i = 1; i <= 6; ++i) {
			std::stringstream file_name;
			file_name << "cow_stay_" << i << ".png";
			cow_stay_anim->addSpriteFrameWithFile(file_name.str());
		}
		cow_stay_anim->setDelayPerUnit(0.2f);
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

	return sprite;
}

void GameScene::update(float dt) {

	//this->GameLogic();
	Point gravity = Vec2(0.0, -9.8);
//	Point gravityStep = Mult(gravity, dt);

//	self.velocity = ccpAdd(self.velocity, gravityStep);
//	CGPoint stepVelocity = ccpMult(self.velocity, dt);

//	// 5
//	self.position = ccpAdd(self.position, stepVelocity);

}

// on "init" you need to initialize your instance
bool GameScene::init() {

	if ( !Scene::init() ) {
		return false;
	}

	try {
		LayerColor* blueSky = LayerColor::create(Color4B::BLACK);
		this->addChild(blueSky, LayerType::BACKGROUND);

		mapLayer = BuildMapLayer(currentLevel);
		this->addChild(mapLayer, LayerType::MAP);

		cow_sprite = BuildSprite(UnitType::COW);
		mapLayer->addChild(cow_sprite, LayerType::SPRITES);

		auto fruit_sprite = BuildSprite(UnitType::APPLE);
		mapLayer->addChild(fruit_sprite, LayerType::SPRITES);

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


