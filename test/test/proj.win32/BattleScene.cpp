#include "BattleScene.h"

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

		// buttons
		// Create menu items
        CCMenuItemImage *pUpButton = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(Battle::upButton));
		CCMenuItemImage *pDownButton = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(Battle::downButton));
		
		CCMenu *menu = CCMenu::create(pUpButton, pDownButton, NULL);
		menu->setPosition(CCPointZero);
		pUpButton->setPosition( ccp(winSize.width/2 - 20,50) );
		pDownButton->setPosition( ccp(winSize.width/2 + 20,50) );
		this->addChild(menu, 1);

		// Call game logic
		this->schedule( schedule_selector(Battle::gameLogicBackgound), 0.0 );
		this->schedule( schedule_selector(Battle::gameLogicPlayer), 0.0 );
		this->schedule( schedule_selector(Battle::gameLogicTarget), 1.0 );

		//this->setTouchEnabled(true);
		//CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);

		bRet = true;

    } while (0);

    return bRet;
}

void Battle::movePlayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	velocityX = velocity * cos(alfa*3.14159/180);
	velocityY = velocity * sin(alfa*3.14159/180);

	//----- Player on the screen -----
	if(actualX < winSize.width/2)
	{
		player->setPosition( ccp(player->getPositionX() + velocityX, player->getPositionY()) );
	}
	player->setPositionY( player->getPositionY() + velocityY );
	player->setRotation(-alfa);
	
	actualX += velocityX;
	actualY += velocityY;

	//----- player out of the screen -----
	// *** left border ***
	if(actualX < 0 && alfa != 0 && flag)
	// saving point of leaving screen and changing flag
	{
		leaveY = actualY;
		flag = false;
	}
	else if(actualX > 0 && !flag)
	{
		flag = true;
	}
	if(actualX < -30 && alfa != 0)
	// change alfa when all picture of player leave screen
	{
		alfa = 180;
	}
	if(actualX < -100 && alfa != 0)
	// return of player on the screen
	{
		alfa = 0;
		actualY = leaveY;
		player->setPositionY(actualY);
	}

	// *** top border ***

}

void Battle::moveBackgraund()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCRect rect = background->getTextureRect();
	if(actualX >= winSize.width/2)
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
}

void Battle::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	// Player
	int speed = 5;
	player->setPosition( ccp(player->getPositionX() + speed, player->getPositionY()) );
}

void Battle::upButton(CCObject* pSender)
{
	alfa+=30;
}

void Battle::downButton(CCObject* pSender)
{
	alfa-=30;
}