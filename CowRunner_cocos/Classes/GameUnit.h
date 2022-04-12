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
		initNumberOfFramesAndDelays();
		names_of_state[UnitState::STAND] = BuildAnimationName("stand");
		names_of_state[UnitState::WAIT] = BuildAnimationName("wait");
		names_of_state[UnitState::WALK] = BuildAnimationName("walk");
		names_of_state[UnitState::RUN] = BuildAnimationName("run");
		names_of_state[UnitState::JUMP] = BuildAnimationName("jump");
	}

	void SetState(const UnitState st) { state = st; }
	int GetNumberOfFrames() const { return anims_frames_and_delays.at(state).first;	}
	float GetAnimationDelay() const { return anims_frames_and_delays.at(state).second;	}
	std::string GetAnimationName(const UnitState st) const { return names_of_state.at(st); }


private:
	std::string unit_name;
	UnitState state;
	// pair<количество кадров, задержка между кадрами>
	std::unordered_map<UnitState, std::pair<int, float>> anims_frames_and_delays;
	std::unordered_map<UnitState, std::string> names_of_state;

	void initNumberOfFramesAndDelays() {
		if (unit_name == "cow") {
			anims_frames_and_delays[UnitState::STAND] = {13, 0.08};
			anims_frames_and_delays[UnitState::WALK] = {11, 0.07};
			anims_frames_and_delays[UnitState::RUN] = {14, 0.02};
			anims_frames_and_delays[UnitState::JUMP] = {0, 0};
			anims_frames_and_delays[UnitState::WAIT] = {0, 0};
		}
		else if (unit_name == "enemy") {
			anims_frames_and_delays[UnitState::STAND] = {0, 0};
			anims_frames_and_delays[UnitState::WALK] = {0, 0};
			anims_frames_and_delays[UnitState::RUN] = {0, 0};
			anims_frames_and_delays[UnitState::JUMP] = {0, 0};
			anims_frames_and_delays[UnitState::WAIT] = {0, 0};
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
	~GameUnit() {
		//cocos2d::AnimationCache::getInstance()->destroyInstance();
		CC_SAFE_DELETE(sprite);
	}

	cocos2d::Sprite* getSprite() { return sprite; }
	void setSprite(cocos2d::Sprite* s) { sprite = s; }

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
	UnitJumpStatus jump_status = DOWN;
	std::string unit_name;
	AnimationManager anim_manager;

	cocos2d::Animation* CreateAnimation(const UnitState action, unsigned int loops);
	void updateUnitAnimation();
};

#endif // GAMEUNIT_H
