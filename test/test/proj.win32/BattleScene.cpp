#include "BattleScene.h"
#include "math.h"

using namespace cocos2d;

CCScene* Battle::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Battle *layer = Battle::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Battle::init()
{
    bool bRet = false;
    do 
    {
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		velocity = 2;
		alfa = 0;
		velocityX = 0;
		velocityY = 0;
		actualX = 0;
		actualY = winSize.height/2;
		leaveX = 0;
		leaveY = 0;
		flag = true;
		
		// Backgraund
		CCSprite* pBackSprite = CCSprite::create("back.png");
		// Place the sprite on the center of the screen
		pBackSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pBackSprite, 0);

		// Player // Repeat Texture Bind
		player = CCSprite::create("Player.png");
		player->setScale(0.5);
		player->setPosition( ccp(actualX, actualY) );
		this->addChild(player);

		// move background
		background = CCSprite::create("moveBack.png");
		ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		background->getTexture()->setTexParameters(&params);
		background->setPosition( ccp(background->getContentSize().width/2,background->getContentSize().height/2) );
		this->addChild(background);

		// Call game logic
		this->schedule( schedule_selector(Battle::gameLogicBackgound), 0.0 );
		this->schedule( schedule_selector(Battle::gameLogicPlayer), 0.0 );
		this->schedule( schedule_selector(Battle::gameLogicTarget), 1.0 );

		CCDirector::sharedDirector()->getKeyboardDispatcher()->addDelegate(this);

		bRet = true;

    } while (0);

    return bRet;
}

void Battle::movePlayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	velocityX = velocity * cos(alfa*M_PI/180);
	velocityY = velocity * sin(alfa*M_PI/180);

	//----- Player on the screen -----
	if(actualX <= winSize.width/2 || actualX >= (2048-winSize.width/2))
	{
		player->setPositionX(player->getPositionX() + velocityX);
	}
	player->setPositionY( player->getPositionY() + velocityY );
	player->setRotation(-alfa);

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
		player->setPositionY(actualY);
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
		player->setPositionY(actualY);
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
		if(player->getPositionX() > winSize.width/2-velocity && player->getPositionX() < winSize.width/2+velocity )
		{
			leaveX = winSize.width/2;
		}
		else
		{

			leaveX = player->getPositionX();
		}
		player->setPositionX(leaveX);
	}
	
	actualX += velocityX;
	actualY += velocityY;
}

void Battle::moveBackgraund()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCRect rect = background->getTextureRect();
	if(actualX > winSize.width/2 && actualX < (2048-winSize.width/2))
	{
		if(rect.origin.x > 4096){
			background->setTextureRect(CCRectMake(0,rect.origin.y,rect.size.width,rect.size.height));
		} else {
			background->setTextureRect(CCRectMake(rect.origin.x+velocityX,rect.origin.y,rect.size.width,rect.size.height));
		}
	}
}

void Battle::addTarget()
{
    CCSprite *target = CCSprite::create("parachute.png");
	target->setScale(float(0.05));

    // Determine where to spawn the target along the Y axis
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height
                          -  target->getContentSize().height/2;
    int rangeY = maxY - minY;
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + minY;

    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( 
        ccp(winSize.width + (target->getContentSize().width/2), 
        50) );
    this->addChild(target);

    // Determine speed of the target
    int minDuration = (int)10.0;
    int maxDuration = (int)15.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration )
                                        + minDuration;

    // Create the actions
    CCFiniteTimeAction* actionMove = 
        CCMoveTo::create( (float)actualDuration, 
        ccp(0 - target->getContentSize().width/2, actualY) );
    CCFiniteTimeAction* actionMoveDone = 
        CCCallFuncN::create( this, 
        callfuncN_selector(Battle::spriteMoveFinished));
    target->runAction( CCSequence::create(actionMove, 
        actionMoveDone, NULL) );
}

void Battle::gameLogicBackgound(float dt)
{
	this->moveBackgraund();
}

void Battle::gameLogicTarget(float dt)
{
	this->addTarget();
}
void Battle::gameLogicPlayer(float dt)
{
	this->movePlayer();
}

void Battle::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
	CCDirector::sharedDirector()->getKeyboardDispatcher()->removeDelegate(this);
}

void Battle::keyUp(int keyCode)
{
	if(keyCode == 38)
	{// up key
		alfa+=5;
	}
	else if(keyCode == 40)
	{// down key
		alfa-=5;
	}
	else if(keyCode == 39)
	{// right key
		alfa-=5;
	}
	else if(keyCode == 37)
	{// left key
		alfa+=5;
	}
}

void Battle::keyDown(int keyCode)
{
	if(keyCode == 38)
	{// up key
		alfa+=5;
	}
	else if(keyCode == 40)
	{// down key
		alfa-=5;
	}
	else if(keyCode == 39)
	{// right key
		alfa-=5;
	}
	else if(keyCode == 37)
	{// left key
		alfa+=5;
	}
}