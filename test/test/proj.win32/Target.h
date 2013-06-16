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
	int view;

	void update(float dt);
	void addTarget(float dt);
	void findPlayer();

public:
	static Player *player;
	static Target* create();
};

#endif  // __TARGET_H__