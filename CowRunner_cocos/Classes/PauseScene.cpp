#include "PauseScene.h"


USING_NS_CC;


Scene* PauseScene::createScene() {
	return PauseScene::create();
}


// on "init" you need to initialize your instance
bool PauseScene::init() {
	//////////////////////////////
	// 1. super init first
	if ( !Scene::init() ) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

Vector<MenuItem*> PauseScene::CreateMenuItems() {

	Vector<MenuItem*> menuItems;

	auto continueItem = MenuBtnBuilder(
				"start_btn_1.png",
				"start_btn_2.png",
				CC_CALLBACK_1(PauseScene::menuContinueGameCallback, this));
	if (continueItem) {
		menuItems.pushBack(continueItem);
	}

	auto exitItem = MenuBtnBuilder(
				"exit_btn_1.png",
				"exit_btn_2.png",
				CC_CALLBACK_1(PauseScene::menuExitToStartMenuCallback, this));
	if (exitItem) {
		menuItems.pushBack(exitItem);
	}

	return menuItems;
}

void PauseScene::menuContinueGameCallback(Ref* pSender) {
	Director::getInstance()->popScene();
}

void PauseScene::menuExitToStartMenuCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFlipY::create(SCENE_CHANGE_TIME, StartMenuScene::createScene()));
}

