#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "keyboard_dispatcher\CCKeyboardDispatcher.h"
#include "Player.h"
#include "Bullet.h"
#include "Target.h"

#define LEFT_KEY 37
#define RIGHT_KEY 39
#define UP_KEY 38
#define DOWN_KEY 40
#define A_KEY 65
#define D_KEY 68
#define W_KEY 87
#define S_KEY 83

using namespace cocos2d;
class Player;

class Battle : public CCLayer, public cocos2d::CCKeyboardDelegate
{
protected:
	CCSprite *background;
	Player *player;
	bool keyLeftFlag;
	bool keyRightFlag;

	void moveBackgraund(float dt);
	void fireSomeBullets(float dt);
	void rotatePlayerLeft(float dt);
	void rotatePlayerRight(float dt);

	void keyUp(int keyCode);
	void keyDown(int keyCode);

	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(Battle);
};

#endif  // __BATTLE_SCENE_H__