#include "Bullet.h"

Bullet* Bullet::create(CCPoint pointIn, int alfaIn, float velocityIn)
{
	Bullet *bul = new Bullet(); 
	bul->alfa = alfaIn;
	bul->velocity = velocityIn;
	bul->initWithFile("bullet.png");
	bul->setPosition( ccp(pointIn.x, pointIn.y) );
	bul->setRotation(-alfaIn);

	bul->schedule( schedule_selector(Bullet::update), 0.0 );

	return bul;
}

void Bullet::update(float dt)
{
	int randError = rand() % 30 + 1;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->setPosition( ccp(
		this->getPositionX() + (velocity+2)*cos(alfa*M_PI/180),
		this->getPositionY() + (velocity+2)*sin(alfa*M_PI/180)));
}
