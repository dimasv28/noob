#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class Player : public CCSprite
{
protected:
	float velocity,velocityX,velocityY,actualX,actualY,leaveX,leaveY;
	int alfa;

	void update(float dt);

public:
	static Player* create();
	virtual bool init();
	CCPoint getActualPoint();
	CCPoint getVelocityPoint();
	float getVelocity();
	int getAlfa();
	
	void setAlfa(int newAlfa);
};

#endif  // __PLAYER_H__