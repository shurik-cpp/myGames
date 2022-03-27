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

Scene* StartMenuScene::createScene()
{
	return StartMenuScene::create();
}


// on "init" you need to initialize your instance
bool StartMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Scene::init() ) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// задаем фон для меню
//	DrawNode* background = DrawNode::create();
//	background->drawSolidRect(origin, visibleSize, Color4F(0.6, 0.6, 0.6, 1.0));
//	this->addChild(background);

	// add "Cow splash screen"
	Sprite* cow_sprite = Sprite::create("cow_stay_1.png");//, Rect(11, 107, 133, 99));
	Size cow_sprite_size = cow_sprite->getContentSize();
	if (cow_sprite) {
		// position the sprite on the center of the screen
		cow_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, cow_sprite_size.height / 2));

		// add the sprite as a child to this layer
		this->addChild(cow_sprite, 0);
	}
	else {
		problemLoading("'cow_stay_1.png'");
	}

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


	// ============================== Menu Items: Start, High score, Exit ===============================


	// create menu, it's an autorelease object
	Menu* menu = Menu::createWithArray(this->CreateMenuItems());
	menu->alignItemsVertically();
	menu->setPosition(Vec2(
											origin.x + visibleSize.width/2,
											origin.y + visibleSize.height - menu->getContentSize().height/4));
	this->addChild(menu, 1);

	return true;
}

Vector<MenuItem*> StartMenuScene::CreateMenuItems() {

	Vector<MenuItem*> menuItems;

	auto startItem = MenuBtnBuilder(
				"start_btn_1.png",
				"start_btn_2.png",
				CC_CALLBACK_1(StartMenuScene::menuStartGameCallback, this));
	if (startItem) {
		menuItems.pushBack(startItem);
	}

	auto highScoreItem = MenuBtnBuilder(
				"h_score_btn_1.png",
				"h_score_btn_2.png",
				CC_CALLBACK_1(StartMenuScene::menuHighScoreCallback, this));
	if (highScoreItem) {
		menuItems.pushBack(highScoreItem);
	}

	auto exitItem = MenuBtnBuilder(
				"exit_btn_1.png",
				"exit_btn_2.png",
				CC_CALLBACK_1(StartMenuScene::menuExitCallback, this));
	if (exitItem) {
		menuItems.pushBack(exitItem);
	}

	return menuItems;
}

void StartMenuScene::menuStartGameCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFlipY::create(SCENE_CHANGE_TIME, GameScene::createScene()));
}

void StartMenuScene::menuHighScoreCallback(Ref* pSender) {

}

void StartMenuScene::menuExitCallback(Ref* pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

