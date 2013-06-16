#include "Target.h"
#include "math.h"

bool addTargetDone = false;

Target* Target::create()
{
	Target *target = new Target();
	target->velocity = -2;
	target->alfa = 0;
	target->view = 90;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	target->initWithFile("target.png");
	target->setPosition( ccp(winSize.width + target->getContentSize().width/2, 500) );
	target->setScale(0.5);

	target->schedule( schedule_selector(Target::addTarget), 0.0 );

	return target;
}

void Target::update(float dt)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	double x1 = getPositionX();
	double y1 = getPositionY();
	double x2 = player->getPositionX();
	double y2 = player->getPositionY();

	double betta = atan((y2 - y1)/(x2 - x1))*180/M_PI;
	int alfaNew = alfa - 180;
	int aaa = alfa - 180 - view/2;
	int bbb = alfa - 180 + view/2;

	//if(betta >= aaa && betta <= bbb)
	//{
		if(betta > alfa-180)
		{
			alfa+=1;
		}
		else
		{
			alfa-=1;
		}
		setRotation(-alfa);
	//}
	//else
	//{
	//	findPlayer();
	//}
	
	float sss = player->getPositionX();
	if(player->getPositionX() == winSize.width/2)
	{
		setPositionX(getPositionX() + (velocity*cos(alfa*M_PI/180) - player->getVelocityPoint().x));
	}
	else
	{
		setPositionX(getPositionX() + (velocity)*cos(alfa*M_PI/180));
	}
	setPositionY(getPositionY() + (velocity)*sin(alfa*M_PI/180));
}

void Target::addTarget(float dt)
{
	int randError = rand() % 100 + 50;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if(player->getPositionX() == winSize.width/2)
	{
		setPositionX(getPositionX() + (velocity*cos(alfa*M_PI/180) - player->getVelocityPoint().x));
	}
	else
	{
		setPositionX(getPositionX() + (velocity)*cos(alfa*M_PI/180));
	}

	if (getPositionX() < player->getPositionX())
	{
		this->unschedule( schedule_selector(Target::addTarget) );
		this->schedule( schedule_selector(Target::update), 0.0 );
	}

}

void Target::findPlayer()
{

	alfa+=1;
	setRotation(-alfa);
}