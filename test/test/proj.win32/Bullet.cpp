#include "Bullet.h"

bool Bullet::init()
{
    bool bRet = false;
    do 
    {
		
		bRet = true;

    } while (0);

    return bRet;
}


Bullet* Bullet::create(CCPoint point, int alfa)
{
	Bullet *bul = new Bullet(); 
	bul->alfaProt = alfa;
	bul->initWithFile("bullet.png");
	bul->setPosition( ccp(point.x+20, point.y) );
	bul->setRotation(-alfa);

	bul->schedule( schedule_selector(Bullet::update), 0.0 );

	return bul;

	// Move bullet to actual endpoint
	/*bullet->runAction( CCSequence::create(
		CCMoveTo::create(velocity+2,
			ccp(player->getPositionX() + 1000*cos(alfa*M_PI/180) + randError,
			player->getPositionY() + 1000*sin(alfa*M_PI/180) + randError)),
		CCCallFuncN::create(this, 
			callfuncN_selector(Battle::spriteMoveFinished)),NULL) );*/
}

void Bullet::update(float dt)
{
	float velocity = 4;
	int randError = rand() % 30 + 1;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->setPosition( ccp(
		this->getPositionX() + velocity*cos(alfaProt*M_PI/180),
		this->getPositionY() + velocity*sin(alfaProt*M_PI/180)));
}
