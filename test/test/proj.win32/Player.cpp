#include "Player.h"
#include "math.h"


// on "init" you need to initialize your instance
bool Player::init()
{
    bool bRet = false;
    do 
    {
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();


		bRet = true;
    } while (0);

    return bRet;
}

Player* Player::create()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	Player *player = new Player();
	// init params
	player->velocity = 2;
	player->alfa = 0;
	player->velocityX = 0;
	player->velocityY = 0;
	player->actualX = 0;
	player->actualY = winSize.height/2;
	player->leaveX = 0;
	player->leaveY = 0;
	player->m_bIsDead = false;

	player->initWithFile("player.png");
	player->setScale(0.5);
	player->setPosition( ccp(player->actualX, player->actualY) );

	player->schedule( schedule_selector(Battle::update), 0.0 );

	return player;
}

void Player::update(float dt)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	velocityX = velocity * cos(alfa*M_PI/180);
	velocityY = velocity * sin(alfa*M_PI/180);

	//----- Player on the screen -----
	if(actualX < winSize.width/2 || actualX > (2048-winSize.width/2))
	{
		setPositionX(getPositionX() + velocityX);
	}
	setPositionY( getPositionY() + velocityY );
	setRotation(-alfa);

	//----- player out of the screen -----
	// *** left border ***
	if(actualX <= abs(velocityX) && actualX >= -abs(velocityX) && alfa != 0)
	// saving point of leaving screen and changing flag
	{
		leaveY = actualY;
	}
	else if(actualX <= -30+abs(velocityX) && actualX >= -30-abs(velocityX) && alfa != 0)
	// change alfa when all picture of player leave screen
	{
		alfa = 180;
	}
	else if(actualX <= -100+abs(velocityX) && actualX >= -100-abs(velocityX) && alfa != 0)
	// return player on the screen
	{
		alfa = 0;
		actualY = leaveY;
		setPositionY(actualY);
	}

	// *** right border ***
	if(actualX >= 2048-abs(velocityX) && actualX <= 2048+abs(velocityX) && alfa != 180)
	// saving point of leaving screen and changing flag
	{
		leaveY = actualY;
	}
	else if(actualX >= 2078-abs(velocityX) && actualX <= 2078+abs(velocityX) && alfa != 180)
	// change alfa when all picture of player leave screen
	{
		alfa = 0;
	}
	else if(actualX >= 2148-abs(velocityX) && actualX <= 2148+abs(velocityX) && alfa != 180)
	// return player on the screen
	{
		alfa = 180;
		actualY = leaveY;
		setPositionY(actualY);
	}

	// *** top border ***
	if(actualY >= 600-abs(velocityY) && actualY <= 600+abs(velocityY) && alfa != -90)
	// saving point of leaving screen and changing flag
	{
			leaveX = actualX;
	}
	else if(actualY >= 630-abs(velocityY) && actualY <= 630+abs(velocityY) && alfa != -90)
	// change alfa when all picture of player leave screen
	{
		alfa = 90;
	}
	else if(actualY >= 700 && alfa != -90)
	// return player on the screen
	{
		alfa = -90;
		actualX = leaveX;
		if(getPositionX() > winSize.width/2-velocity && getPositionX() < winSize.width/2+velocity )
		{
			leaveX = winSize.width/2;
		}
		else
		{
			leaveX = getPositionX();
		}
		setPositionX(leaveX);
	}

	// *** bottom border ***
	if(actualY >= 80-abs(velocityY) && actualY <= 80+abs(velocityY))
	// game over
	{
		m_bIsDead = true;
	}
	
	actualX += velocityX;
	actualY += velocityY;
}

CCPoint Player::getActualPoint()
{
	return ccp(actualX,actualY);
}
CCPoint Player::getVelocityPoint()
{
	return ccp(velocityX,velocityY);
}

void Player::setAlfa(int newAlfa)
{
	alfa = newAlfa;
}

int Player::getAlfa()
{
	return alfa;
}

float Player::getVelocity()
{
	return velocity;
}