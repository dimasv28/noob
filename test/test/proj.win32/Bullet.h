#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class Bullet : public CCSprite
{
protected:

	void update();

public:
	static Bullet* create(CCPoint point, int alfa);

    virtual bool init();
};

#endif  // __BULLET_H__