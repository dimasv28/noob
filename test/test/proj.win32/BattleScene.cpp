#include "BattleScene.h"
#include "HelloWorldScene.h"
#include "math.h"
#include <windows.h>


Player* Target::player = NULL;
Player* Bullet::player = NULL;

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
		keyLeftFlag = false;
		keyRightFlag = false;
		
		// add Player
		player = Player::create();
		this->addChild(player, 1);

		Target::player = player;
		Bullet::player = player;

		// Backgraund
		CCSprite* pBackSprite = CCSprite::create("back.png");
		pBackSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
		addChild(pBackSprite, 0);

		// move background
		background = CCSprite::create("moveBack.png");
		ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		background->getTexture()->setTexParameters(&params);
		background->setPosition( ccp(background->getContentSize().width/2,background->getContentSize().height/2) );
		addChild(background);
		
		// add target
		Target *target = Target::create();
		addChild(target);

		// Call game logic
		this->schedule( schedule_selector(Battle::moveBackgraund), 0.0 );

		// enable keyboard
		CCDirector::sharedDirector()->getKeyboardDispatcher()->addDelegate(this);
		// enable touhpad with mouse
		this->setTouchEnabled(true);

		bRet = true;

    } while (0);

    return bRet;
}

void Battle::moveBackgraund(float dt)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float actualX = player->getActualPoint().x;
	float velocityX = player->getVelocityPoint().x;
	CCRect rect = background->getTextureRect();
	if(actualX > winSize.width/2 && actualX < (2048-winSize.width/2))
	{
		if(rect.origin.x > 4096){
			background->setTextureRect(CCRectMake(0,rect.origin.y,rect.size.width,rect.size.height));
		} else {
			background->setTextureRect(CCRectMake(rect.origin.x+velocityX,rect.origin.y,rect.size.width,rect.size.height));
		}
	}

	if(player->isDead())
	{
		CCSprite *gameOver = CCSprite::create("gameover.png");
		gameOver->setPosition( ccp(winSize.width/2,winSize.height/2) );
		addChild(gameOver,200);
		player->pauseSchedulerAndActions();
		pauseSchedulerAndActions();
	}
}

void Battle::keyUp(int keyCode)
{
	unschedule( schedule_selector(Battle::rotatePlayerLeft));
	unschedule( schedule_selector(Battle::rotatePlayerRight));
	keyLeftFlag = false;
	keyRightFlag = false;
	if(keyCode == 27)
	{// exit with Esc
	    CCScene *pHelloScene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(pHelloScene);
	}
}

void Battle::keyDown(int keyCode)
{
	if( (keyCode == LEFT_KEY || keyCode == UP_KEY || keyCode == W_KEY || keyCode == A_KEY) && !keyLeftFlag)
	{// up key
		keyLeftFlag = true;
		keyRightFlag = false;
		schedule( schedule_selector(Battle::rotatePlayerLeft), 0.0 );
		unschedule( schedule_selector(Battle::rotatePlayerRight));
	}
	else if( (keyCode == RIGHT_KEY || keyCode == DOWN_KEY || keyCode == D_KEY || keyCode == S_KEY) && !keyRightFlag)
	{// down key
		keyRightFlag = true;
		keyLeftFlag = false;
		schedule( schedule_selector(Battle::rotatePlayerRight), 0.0 );
		unschedule( schedule_selector(Battle::rotatePlayerLeft));
	}
}

void Battle::fireSomeBullets(float dt)
{
	Bullet *bullet = Bullet::create();
	addChild(bullet);
}

void Battle::rotatePlayerLeft(float dt)
{
	player->setAlfa(player->getAlfa()+5);
}

void Battle::rotatePlayerRight(float dt)
{
	player->setAlfa(player->getAlfa()-5);
}

void Battle::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	this->schedule( schedule_selector(Battle::fireSomeBullets), 0.2 );
}

void Battle::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	this->unschedule( schedule_selector(Battle::fireSomeBullets) );
}
