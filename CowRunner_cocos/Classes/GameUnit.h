#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include <iostream>
#include <unordered_map>
#include "cocos2d.h"

struct isEvents {
	bool isKeyLeft = false;
	bool isKeyRight = false;
	bool isUpKey = false;
	bool isDownKey = false;
	bool isShiftKey = false;
	bool is_change_animation = false;
};

enum UnitState {
	STAND,
	WAIT,
	WALK,
	RUN,
	JUMP
};

class AnimationManager {
public:
	AnimationManager(const std::string& name) : unit_name(name) {
		SetNumberOfFrames();
		names_of_state[UnitState::STAND] = BuildAnimationName("stand");
		names_of_state[UnitState::WAIT] = BuildAnimationName("wait");
		names_of_state[UnitState::WALK] = BuildAnimationName("walk");
		names_of_state[UnitState::RUN] = BuildAnimationName("run");
		names_of_state[UnitState::JUMP] = BuildAnimationName("jump");
	}

	int GetNumberOfFrames(const UnitState state) const {
		return anims_frames.at(state);
	}

	std::string GetAnimationName(const UnitState state) const {
		return names_of_state.at(state);
	}

private:
	std::string unit_name;
	std::unordered_map<UnitState, int> anims_frames;
	std::unordered_map<UnitState, std::string> names_of_state;

	void SetNumberOfFrames() {
		if (unit_name == "cow") {
			anims_frames[UnitState::STAND] = 13;
			anims_frames[UnitState::WALK] = 11;
			anims_frames[UnitState::RUN] = 14;
			anims_frames[UnitState::JUMP] = 0;
			anims_frames[UnitState::WAIT] = 0;
		}
		else if (unit_name == "enemy") {
			anims_frames[UnitState::STAND] = 0;
			anims_frames[UnitState::WALK] = 0;
			anims_frames[UnitState::RUN] = 0;
			anims_frames[UnitState::JUMP] = 0;
			anims_frames[UnitState::WAIT] = 0;
		}
	}
	std::string BuildAnimationName(const std::string& action) const {
		std::stringstream ss;
		ss << unit_name << '_' << action;
		return ss.str();
	}
};

class GameUnit {
public:
	explicit GameUnit(const std::string& name)
		: unit_name(name)
		, anim_manager(name) {
	}
	~GameUnit() { CC_SAFE_DELETE(sprite); }

	cocos2d::Sprite* getSprite() { return sprite; }
	void setSprite(cocos2d::Sprite* s) {
		sprite = s;
	}

	void initAnimations();

	void tick(isEvents& events, float delta);

private:
	enum UnitDirection {
		LEFT,
		RIGHT
	};

	enum UnitJumpStatus {
		FLY,
		UP,
		DOWN,
		ON_LAND
	};

	cocos2d::Sprite* sprite = nullptr;
	UnitDirection direction = RIGHT;
	UnitState state = STAND;
	UnitJumpStatus jump = DOWN;
	std::string unit_name;
	AnimationManager anim_manager;

	cocos2d::Animation* CreateAnimation(const UnitState action, float delay, unsigned int loops);
	void updateUnitAnimation();
};

#endif // GAMEUNIT_H
