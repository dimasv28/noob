#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "keyboard_dispatcher\CCKeyboardDispatcher.h"

using namespace cocos2d;

class Battle : public CCLayer, public cocos2d::CCKeyboardDelegate
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

	void keyUp(int keyCode);
	void keyDown(int keyCode);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(Battle);
};

#endif  // __BATTLE_SCENE_H__