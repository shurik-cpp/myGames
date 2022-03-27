#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <iostream>
#include <random>

#include "cocos2d.h"
#include "StartMenuScene.h"


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

	int currentLevel = 2;
	cocos2d::TMXTiledMap* mapLayer = nullptr;
	cocos2d::Sprite* cow_sprite = nullptr;


	cocos2d::TMXTiledMap* BuildMapLayer(int level);
	cocos2d::Sprite* BuildSprite(const UnitType type);

	virtual void update(float dt);

};


#endif // GAMESCENE_H
