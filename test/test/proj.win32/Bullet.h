#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class Bullet : public CCSprite
{
protected:
	float velocity;
	int alfa;

	void update(float dt);

public:
	static Bullet* create(CCPoint pointIn, int alfaIn, float velocityIn);
};

#endif  // __BULLET_H__