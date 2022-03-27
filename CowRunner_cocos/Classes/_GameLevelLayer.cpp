#include "GameLevelLayer.h"



USING_NS_CC;



// on "init" you need to initialize your instance
bool GameLevelLayer::init(const int level) {

//	LayerColor* blueSky = LayerColor::create(Color4B::BLUE);
//	this->addChild(blueSky);

	std::stringstream ss;
	ss << "map_" << level << ".tmx";
	// create a map
	this->map = TMXTiledMap::create(ss.str());
	if (map == nullptr) {
		return false;
	}

	this->addChild(map);


	return true;
}

TMXTiledMap* GameLevelLayer::getCurrentLevel() {
	return map;
}

