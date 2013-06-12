#include "Target.h"
#include "math.h"

Target* Target::create()
{
	Target *target = new Target();
	target->velocity = 2;
	target->alfa = 0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	target->initWithFile("target.png");
	target->setPosition( ccp(winSize.width + target->getContentSize().width, 500) );
	target->setScale(0.5);

	target->schedule( schedule_selector(Target::update), 0.0 );

	return target;
}

void Target::update(float dt)
{
	//int randError = rand() % 30 + 1;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if(getPosition().x < winSize.width/4)
	{
		alfa+=2;
		setRotation(M_PI-alfa);
	}
	/*if(player->getPositionX() <= winSize.width/2 || player->getPositionX() >= (2048-winSize.width/2))
	{
			setPositionX(getPositionX() - velocity*cos(alfa*M_PI/180));
	}
	setPositionY(getPositionY() - velocity*sin(alfa*M_PI/180));*/
	
}
