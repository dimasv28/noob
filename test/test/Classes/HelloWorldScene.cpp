#include "HelloWorldScene.h"
#include "BattleScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		// labels
		CCLabelTTF* playLabel = CCLabelTTF::create("Play", "Arial", 20);
		CCLabelTTF* musicOnLabel = CCLabelTTF::create("Music", "Arial", 20);
		CCLabelTTF* musicOffLabel = CCLabelTTF::create("Music: Off", "Arial", 20);

        // Create menu items
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));

		CCMenuItemLabel *pPlayItem = CCMenuItemLabel::create(playLabel,this,menu_selector(HelloWorld::menuPlayCallback));
		CCMenuItemLabel *pMusicItem = CCMenuItemLabel::create(musicOnLabel,this,menu_selector(HelloWorld::menuMusicCallback));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pPlayItem, pMusicItem, pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pPlayItem->setPosition(ccp(size.width / 2, size.height - 50));
		pMusicItem->setPosition(ccp(size.width / 2, size.height - 80));
		pCloseItem->setPosition(ccp(size.width - 20, 20));

        // Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::menuPlayCallback(CCObject* pSender)
{
	// create a scene. it's an autorelease object
    CCScene *pPlayScene = Battle::scene();

    // "play" menu item clicked
	CCDirector::sharedDirector()->replaceScene(pPlayScene);
}

void HelloWorld::menuMusicCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::sharedEngine();
	if(!audio->isBackgroundMusicPlaying())
	{
		audio->playBackgroundMusic("akon.mp3", true);
	}
	else
	{
		audio->stopBackgroundMusic();
	}
}