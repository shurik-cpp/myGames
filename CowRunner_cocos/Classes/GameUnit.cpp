#include "GameUnit.h"

USING_NS_CC;

Animation* GameUnit::CreateAnimation(const UnitState action, float delay, unsigned int loops) {
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

void GameUnit::initAnimations() {
	auto animCache = AnimationCache::getInstance();

	animCache->addAnimation(
				CreateAnimation(UnitState::STAND, 0.08, CC_REPEAT_FOREVER),
				anim_manager.GetAnimationName(UnitState::STAND)
				);
	animCache->addAnimation(
				CreateAnimation(UnitState::WALK, 0.07, CC_REPEAT_FOREVER),
				anim_manager.GetAnimationName(UnitState::WALK)
				);



	updateUnitAnimation();
}

void GameUnit::updateUnitAnimation() {
	std::cerr << "Update animation with state = " << state << std::endl;
	static int counterEntryes = 0;
	std::cerr << "counterEntryes = " << counterEntryes << std::endl;
	counterEntryes++;
	sprite->stopAllActions();

	auto animCache = AnimationCache::getInstance();
	sprite->runAction(Animate::create(animCache->getAnimation(anim_manager.GetAnimationName(state))));

	std::cerr << "Update animation success." << std::endl;
}

void GameUnit::tick(isEvents& is_events, float delta) {

	if (is_events.isKeyLeft || is_events.isKeyRight) {
		state = UnitState::WALK;
	} else if ((!is_events.isKeyLeft && !is_events.isKeyRight) ||
						 (is_events.isKeyLeft && is_events.isKeyRight)) {
		state = UnitState::STAND;
	}

	if (state == UnitState::WALK) {
		const float SPEED = 5;//350 * delta;
		float cow_speed = 0;
		if (is_events.isKeyLeft && is_events.isKeyRight) {
			// TODO корова мычит и воспроизводится анимация недовольной коровы (встает на дыбы? :D)
		}	else if (is_events.isKeyLeft) {
			direction = UnitDirection::LEFT;
			cow_speed -= SPEED;
		} else if (is_events.isKeyRight) {
			direction = UnitDirection::RIGHT;
			cow_speed += SPEED;
		}
		sprite->setFlippedX(!static_cast<bool>(direction));

		sprite->setPositionX(sprite->getPositionX() + cow_speed);
	}

	const float cow_posY = sprite->getPositionY();
	const float MAX_JUMP_ACCELERATION = 25; //1000 * delta;  // высота прыжка
	const float JUMP_DELTA = 1; //30 * delta;                // замедление/ускорение
	const float COW_ON_LAND_Y = 125;
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
