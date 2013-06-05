#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Battle : public CCLayer
{
protected:
	CCSprite *background;
	CCSprite *player;
	float velocity,velocityX,velocityY,actualX,actualY,leaveX,leaveY;
	int alfa;
	bool flag; // for saving point of leaving screen just once

	void gameLogicBackgound(float dt);
	void gameLogicTarget(float dt);
	void gameLogicPlayer(float dt);
	void spriteMoveFinished(CCNode* sender);
	void addTarget();
	void moveBackgraund();
	void movePlayer();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void upButton(CCObject* pSender);
	void downButton(CCObject* pSender);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(Battle);
};

#endif  // __BATTLE_SCENE_H__