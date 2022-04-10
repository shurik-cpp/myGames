#include "GameUnit.h"

USING_NS_CC;

Animation* GameUnit::CreateAnimation(const UnitState action, float delay, unsigned int loops)
{
	auto animation = Animation::create();
	auto cow_frame_cache = SpriteFrameCache::getInstance(); // кеш загружен в AppDeligate.cpp ( spritecache->addSpriteFramesWithFile("res/cow/cow_stay_sheet.plist"); )

	for (int i = 1; i <= anim_manager.GetNumberOfFrames(action); i++) {
		std::stringstream file_name;
		file_name << "./" << anim_manager.GetAnimationName(action) << '_' << i;
		//std::cout << file_name.str() << std::endl;
		animation->addSpriteFrame(cow_frame_cache->getSpriteFrameByName(file_name.str()));
	}
	animation->setDelayPerUnit(delay);// / 6.0f); // This animation contains 14 frames, will     continuous 2.8 seconds.
	animation->setLoops(loops);
	return animation;
}

void GameUnit::initAnimations()
{
	auto animCache = AnimationCache::getInstance();

	animCache->addAnimation(
				CreateAnimation(UnitState::STAND, 0.08, CC_REPEAT_FOREVER),
				anim_manager.GetAnimationName(UnitState::STAND)
				);
	animCache->addAnimation(
				CreateAnimation(UnitState::WALK, 0.07, CC_REPEAT_FOREVER),
				anim_manager.GetAnimationName(UnitState::WALK)
				);
	animCache->addAnimation(
				CreateAnimation(UnitState::RUN, 0.02, CC_REPEAT_FOREVER),
				anim_manager.GetAnimationName(UnitState::RUN)
				);

	updateUnitAnimation();
}

void GameUnit::updateUnitAnimation()
{
	sprite->stopAllActions();
	auto animCache = AnimationCache::getInstance();
	sprite->runAction(Animate::create(animCache->getAnimation(anim_manager.GetAnimationName(state))));
}

void GameUnit::tick(isEvents& is_events, float delta)
{
	if ((is_events.isKeyLeft && !is_events.isShiftKey) ||
			(is_events.isKeyRight && !is_events.isShiftKey)) {
		state = UnitState::WALK;
	} else if ((is_events.isKeyLeft && is_events.isShiftKey) ||
						 (is_events.isKeyRight && is_events.isShiftKey)) {
		state = UnitState::RUN;
	} else if ((!is_events.isKeyLeft && !is_events.isKeyRight) ||
						 (is_events.isKeyLeft && is_events.isKeyRight)) {
		state = UnitState::STAND;
	}


	float cow_speed = 0; //350 * delta;
	if (state == UnitState::WALK) {
		cow_speed = 5;
	} else if (state == UnitState::RUN) {
		cow_speed = 12;
	}

	if (is_events.isKeyLeft && is_events.isKeyRight) {
		// TODO корова мычит и воспроизводится анимация недовольной коровы (встает на дыбы? :D)
		state = UnitState::STAND;
		cow_speed = 0;
	}	else if (is_events.isKeyLeft) {
		direction = UnitDirection::LEFT;
		cow_speed *= -1;
	} else if (is_events.isKeyRight) {
		direction = UnitDirection::RIGHT;
		//cow_speed *= 1;
	}
	sprite->setFlippedX(!static_cast<bool>(direction));
	sprite->setPositionX(sprite->getPositionX() + cow_speed);


	const float cow_posY = sprite->getPositionY();
	const float MAX_JUMP_ACCELERATION = 30; //1000 * delta;  // высота прыжка
	const float JUMP_DELTA = 1.5; //std::rand() % 5; //30 * delta;                // замедление/ускорение
	const float COW_ON_LAND_Y = 105;
	static float jump_acceleration = 0;

	if (jump == UnitJumpStatus::ON_LAND) {
		if (is_events.isUpKey) {
			jump = UnitJumpStatus::UP;
		}
	}
	if (is_events.isDownKey) {
		jump = UnitJumpStatus::DOWN;
	}

	if (jump == UnitJumpStatus::UP) {
		jump_acceleration = MAX_JUMP_ACCELERATION;
		jump = UnitJumpStatus::FLY;
	}
	else if (jump == UnitJumpStatus::FLY) {
		if (jump_acceleration > 0) {
			sprite->setPositionY(cow_posY + jump_acceleration);
			jump_acceleration -= JUMP_DELTA;
		} else {
			jump = UnitJumpStatus::DOWN;
			jump_acceleration = 0;
			is_events.is_change_animation = true;
		}
	}
	else if (jump == UnitJumpStatus::DOWN) {
		if (cow_posY >= COW_ON_LAND_Y) {
			sprite->setPositionY(cow_posY - jump_acceleration);
			if (jump_acceleration < MAX_JUMP_ACCELERATION) {
				jump_acceleration += JUMP_DELTA;
			}
		}
		else {
			sprite->setPositionY(COW_ON_LAND_Y);
			jump = UnitJumpStatus::ON_LAND;
			jump_acceleration = 0;
			is_events.is_change_animation = true;
		}
	}

	if (is_events.is_change_animation) {
		is_events.is_change_animation = false;
		updateUnitAnimation();
	}
}
