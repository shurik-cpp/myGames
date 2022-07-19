#ifndef STARTMENUSCENE_H
#define STARTMENUSCENE_H

#include "cocos2d.h"
#include "GameScene.h"

const float SCENE_CHANGE_TIME = 0.5;

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/'");
}

cocos2d::MenuItem* MenuBtnBuilder(const std::string& normalImage,
																	const std::string& selectedImage,
																	const cocos2d::ccMenuCallback& callback);

class StartMenuScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(StartMenuScene);


private:
	// a selector callback
	void menuStartGameCallback(cocos2d::Ref* pSender);
	void menuHighScoreCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

	cocos2d::Vector<cocos2d::MenuItem*> CreateMenuItems();
};



#endif // STARTMENUSCENE_H
