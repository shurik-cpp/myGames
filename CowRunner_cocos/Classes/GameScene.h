#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <iostream>
#include <random>
//#include <vector>

#include "cocos2d.h"
#include "StartMenuScene.h"

enum UnitDirection {
	LEFT,
	RIGHT
};
enum UnitState {
	STOP,
	GRAZE,
	WALK,
	RUN
};
enum UnitJumpStatus {
	UP,
	FLY,
	DOWN,
	ON_LAND
};

class GameUnit {
public:
	GameUnit() {}
	~GameUnit() { CC_SAFE_DELETE(sprite); }

	cocos2d::Sprite* getSprite() { return sprite; }
	void setSprite(cocos2d::Sprite* s) {
//		CC_SAFE_DELETE(sprite);
		sprite = s;
	}
	void setDirection(UnitDirection dir) { direction = dir; }
	UnitDirection getDirection() { return direction; }
	void setState(UnitState st) { state = st; }
	UnitState getState() { return state; }
	void setJumpStatus(UnitJumpStatus js) { jump = js; }
	UnitJumpStatus getJumpStatus() { return jump; }

private:
	cocos2d::Sprite* sprite = nullptr;
	UnitDirection direction = RIGHT;
	UnitState state = STOP;
	UnitJumpStatus jump = DOWN;
};


class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene();

private:
	enum LayerType {
		BACKGROUND = -1,
		MAP,
		SPRITES
	};

	enum UnitType {
		COW,
		APPLE,
		ENEMY
	};


	int currentLevel = 2;

	cocos2d::EventListenerKeyboard* eventListener = nullptr;
	cocos2d::TMXTiledMap* mapLayer = nullptr;
	GameUnit cow;

	cocos2d::TMXTiledMap* BuildMapLayer(int level);
	cocos2d::Sprite* BuildSprite(const UnitType type);

	virtual void update(float delta);

};


#endif // GAMESCENE_H
