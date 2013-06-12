#include "Bullet.h"

Bullet* Bullet::create()
{

	Bullet *bul = new Bullet();
	bul->alfa = player->getAlfa();
	bul->velocity = player->getVelocity();
	bul->initWithFile("bullet.png");
	bul->setPosition( ccp(
		player->getPositionX() + player->getContentSize().width/4*cos(bul->alfa*M_PI/180),
		player->getPositionY() + player->getContentSize().height/4*sin(bul->alfa*M_PI/180)) );
	bul->setRotation(-bul->alfa);

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
