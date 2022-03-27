#ifndef GAMELEVELLAYER_H
#define GAMELEVELLAYER_H

#include "cocos2d.h"


class GameLevelLayer : public cocos2d::Layer {
public:

	virtual bool init(const int level = 1);
	cocos2d::TMXTiledMap* getCurrentLevel();


private:
	cocos2d::TMXTiledMap* map = nullptr;

};




#endif // GAMELEVELLAYER_H
