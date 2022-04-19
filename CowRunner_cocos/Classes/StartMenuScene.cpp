#include "StartMenuScene.h"

#include <iostream>

USING_NS_CC;


MenuItem* MenuBtnBuilder(const std::string& normalImage,
												 const std::string& selectedImage,
												 const ccMenuCallback& callback) {

	auto item = MenuItemImage::create(normalImage, selectedImage, callback);

	if (item == nullptr ||
			item->getContentSize().width <= 0 ||
			item->getContentSize().height <= 0) {
		std::cerr << "Error while loading: '" << normalImage << "' and '" << selectedImage << "'\n" <<
								 "Depending on how you compiled you might have to add 'Resources/'\n";
	}
	return item;
}

Scene* StartMenuScene::createScene() {
	return StartMenuScene::create();
}


// on "init" you need to initialize your instance
bool StartMenuScene::init() {
	//////////////////////////////
	// 1. super init first
	if ( !Scene::init() ) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// задаем фон для меню
	Color4B blueSkyColor(Color3B(184, 237, 255));
	LayerColor* backgroundLayer = LayerColor::create(blueSkyColor);
	this->addChild(backgroundLayer, -1);

	const Vec2 grass_pos(-300, 0);
	const Vec2 grass_anchor(0, 0);
	const std::pair<float, float> sprites_scale = {0.9, 0.9};
	Sprite* grass_back = Sprite::create("res/world/grass_back.png");
	grass_back->setScale(sprites_scale.first, sprites_scale.second);
	grass_back->setAnchorPoint(grass_anchor);
	grass_back->setPosition(grass_pos);
	this->addChild(grass_back, -1);

	Sprite* grass_front = Sprite::create("res/world/grass_front.png");
	grass_front->setScale(sprites_scale.first, sprites_scale.second);
	grass_front->setAnchorPoint(grass_anchor);
	grass_front->setPosition(grass_pos);
	this->addChild(grass_front, 2);


	// add "Cow splash screen"
	Sprite* cow_sprite = Sprite::create();

	// position the sprite on the center of the screen
	cow_sprite->setScale(sprites_scale.first, sprites_scale.second);
	cow_sprite->setAnchorPoint(Vec2(0.5, 0));
	cow_sprite->setPosition(Vec2(visibleSize.width / 4, 40));

	auto cow_frame_cache = SpriteFrameCache::getInstance();// кеш загружен в AppDeligate.cpp ( spritecache->addSpriteFramesWithFile("res/cow/cow_stay_sheet.plist"); )

	Animation* cow_stay_anim = Animation::create();
	for (int i = 1; i <= 13; i++) {
		std::stringstream file_name;
		file_name << "./cow_stand_" << i;
		//std::cout << file_name.str() << std::endl;
		cow_stay_anim->addSpriteFrame(cow_frame_cache->getSpriteFrameByName(file_name.str()));
	}

	cow_stay_anim->setDelayPerUnit(0.08f);// / 6.0f); // This animation contains 14 frames, will     continuous 2.8 seconds.
	cow_stay_anim->setLoops(CC_REPEAT_FOREVER);

	//Animate* action = Animate::create(cow_stay_anim);

	// run action on sprite object
	cow_sprite->runAction(Animate::create(cow_stay_anim));

	// add the sprite as a child to this layer
	this->addChild(cow_sprite, 0);



	//Vector<Sprite*> clouds = ;



	// ============================== Menu Items: Start, High score, Exit ===============================
	const std::pair<float, float> menu_scale = {0.5, 0.5};

	Sprite* vertical_pointer = Sprite::create("res/pointer/pointer_vertical.png");
	if (vertical_pointer) {
		vertical_pointer->setScale(menu_scale.first, menu_scale.second);
		vertical_pointer->setAnchorPoint(Vec2(0.5, 0));
		vertical_pointer->setPosition(Vec2((visibleSize.width / 3) * 2 + 20, 10));
		this->addChild(vertical_pointer, 0);

		// create menu, it's an autorelease object
		Menu* menu = Menu::createWithArray(this->CreateMenuItems());
		menu->alignItemsVertically();
		menu->setAnchorPoint(Vec2(0.5, 0.0));
		menu->setPosition(Vec2(50.0, 650.0));
		vertical_pointer->addChild(menu, 1);
	}



	return true;
}

Vector<MenuItem*> StartMenuScene::CreateMenuItems() {

	Vector<MenuItem*> menuItems;

	auto startItem = MenuBtnBuilder(
				"res/pointer/pointer_start_default.png",
				"res/pointer/pointer_start_selected.png",
				CC_CALLBACK_1(StartMenuScene::menuStartGameCallback, this));
	if (startItem) {
		menuItems.pushBack(startItem);
	}

	auto highScoreItem = MenuBtnBuilder(
				"res/pointer/pointer_high_score_default.png",
				"res/pointer/pointer_high_score_selected.png",
				CC_CALLBACK_1(StartMenuScene::menuHighScoreCallback, this));
	if (highScoreItem) {
		menuItems.pushBack(highScoreItem);
	}

	auto exitItem = MenuBtnBuilder(
				"res/pointer/pointer_exit_default.png",
				"res/pointer/pointer_exit_selected.png",
				CC_CALLBACK_1(StartMenuScene::menuExitCallback, this));
	if (exitItem) {
		menuItems.pushBack(exitItem);
	}

	return menuItems;
}

void StartMenuScene::menuStartGameCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(GameScene::createScene()); // (TransitionFlipY::create(SCENE_CHANGE_TIME, GameScene::createScene()));
}

void StartMenuScene::menuHighScoreCallback(Ref* pSender) {

}

void StartMenuScene::menuExitCallback(Ref* pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

