#ifndef __COW_SCENE_H__
#define __COW_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "StartMenuScene.h"
#include "PauseScene.h"

// PTM_RATIO - сколько пикселей на экране составляет 1 метр, 32 означает, что
// 32 пикселя на экране означает 1 метр, единица измерения в Box2D использует метрическую систему MKS, то есть:
// единицы измерения длины - метры, качество - килограммы, единицы времени - секунды.
#define PTM_RATIO 32

enum class UnitDirection {
	LEFT,
	RIGHT
};

enum class UnitState {
	STOP,
	GRAZE,
	WALK,
	RUN
};

class Cow : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(Cow);

	~Cow();

private:
	UnitDirection cow_direction;
	UnitState cow_state;
	bool cow_jump = false;

	cocos2d::Sprite* cow_sprite = nullptr;


	virtual void update(float dt);
	void GameLogic();

	void initPhysics();

	void CreateFruit();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

};

#endif // __COW_SCENE_H__
