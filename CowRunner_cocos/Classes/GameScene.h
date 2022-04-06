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
	explicit GameUnit() {}
	~GameUnit() { CC_SAFE_DELETE(sprite); }

	cocos2d::Sprite* getSprite() { return sprite; }
	void setSprite(cocos2d::Sprite* s) {
		sprite = s;
	}
	void setDirection(const UnitDirection dir) { direction = dir; }
	UnitDirection getDirection() const { return direction; }
	void setState(const UnitState st) { state = st; }
	UnitState getState() const { return state; }
	void setJumpStatus(const UnitJumpStatus js) { jump = js; }
	UnitJumpStatus getJumpStatus() const { return jump; }
	//============================ IMPLEMENT THIS! =====================================
	void setUnitAnimation(cocos2d::Animate* anim);
	void updateUnitAnimation();
	//==================================================================================
	struct Animations {
		cocos2d::Animate* state;
		cocos2d::Animate* walk;
		cocos2d::Animate* jump_up;
		cocos2d::Animate* jump_down;
		cocos2d::Animate* run;
	};
	//==================================================================================
private:
	cocos2d::Sprite* sprite = nullptr;
	UnitDirection direction = RIGHT;
	UnitState state = STOP;
	UnitJumpStatus jump = DOWN;
	//==================================================================================
	Animations animations;
	//==================================================================================
};


class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene();

private:
	enum LayerType {
		BACKGROUND = -1,
		MAP,
		SPRITES,
		FRONT
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

	bool isKeyLeft = false;
	bool isKeyRight = false;
	bool isUpKey = false;


};


#endif // GAMESCENE_H
