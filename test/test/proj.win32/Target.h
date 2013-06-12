#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class Target : public CCSprite
{
protected:
	float velocity;
	int alfa;

	void update(float dt);

public:
	static CCSprite *player;
	static float *playerVelocityX;
	static float *playerVelocityY;
	static Target* create();
	virtual bool init();
};

#endif  // __TARGET_H__