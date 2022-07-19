#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "cocos2d.h"
//#include "CowScene.h"
#include "StartMenuScene.h"


class PauseScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);


private:
	// a selector callback
	void menuContinueGameCallback(cocos2d::Ref* pSender);
	void menuExitToStartMenuCallback(cocos2d::Ref* pSender);

	cocos2d::Vector<cocos2d::MenuItem*> CreateMenuItems();
};


#endif // PAUSESCENE_H
