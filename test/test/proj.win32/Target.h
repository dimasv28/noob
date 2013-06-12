#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class Player;

class Target : public CCSprite
{
protected:
	float velocity;
	int alfa;

	void update(float dt);

public:
	static Player *player;
	static Target* create();
};

#endif  // __TARGET_H__