#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class Bullet : public CCSprite
{
protected:

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static node()" method manually
    CREATE_FUNC(Bullet);
};

#endif  // __BULLET_H__