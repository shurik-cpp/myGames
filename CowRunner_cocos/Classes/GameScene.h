#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <iostream>
#include <random>
#include <memory>
#include <vector>

#include "cocos2d.h"
#include "StartMenuScene.h"
#include "GameUnit.h"

class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	virtual void update(float delta) override;

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

	enum UnitType { COW, APPLE, ENEMY };

	int currentLevel = 0;

	cocos2d::EventListenerKeyboard* eventListener = nullptr;
	cocos2d::TMXTiledMap* mapLayer = nullptr;
	const float objects_scale_XY = 0.9;
	std::shared_ptr<GameUnit> cow;

	cocos2d::TMXTiledMap* BuildMapLayer(int level);
	cocos2d::Sprite* BuildSprite(const UnitType type);

	isEvents is_events;

};


#endif // GAMESCENE_H
