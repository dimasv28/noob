#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class Player;

class Bullet : public CCSprite
{
protected:
	float velocity;
	int alfa;

	void update(float dt);

public:
	static Player *player;
	static Bullet* create();
};

#endif  // __BULLET_H__