#include "LevelBrowserLayer.h"
#include "GameLevelManager.h"
#include "AppDelegate.h"
USING_NS_CC;

CCScene* LevelBrowserLayer::scene(GJSearchObject* searchObject)
{
	// 'scene' is an autorelease object
	CCScene* scene = CCScene::create();

	AppDelegate* pApp = AppDelegate::get();
	pApp->setScenePointer(scene);

	// 'layer' is an autorelease object
	LevelBrowserLayer* layer = LevelBrowserLayer::create(searchObject);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

LevelBrowserLayer* LevelBrowserLayer::create(GJSearchObject* searchObject)
{
	LevelBrowserLayer* pRet = new LevelBrowserLayer();
	if (pRet && pRet->init(searchObject))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool LevelBrowserLayer::init(GJSearchObject* searchObject)
{
	if (!CCLayer::init())
		return false;

	GameLevelManager::sharedState()->setLastSearchType(searchObject->getType());
	this->setKeypadEnabled(true);

	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCSprite* bgSprite = CCSprite::create("GJ_gradientBG.png");
	bgSprite->setAnchorPoint(ccp(0.0f, 0.0f));
	this->addChild(bgSprite, -2);

	bgSprite->setScaleX((winSize.width + 10.0f) / bgSprite->getContentSize().width);
	bgSprite->setScaleY((winSize.height + 10.0f) / bgSprite->getContentSize().height);
	bgSprite->setPosition(ccp(-5.0f, -5.0f));
	bgSprite->setColor(ccc3(0, 102, 225));

	CCSprite* sideArtL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	sideArtL->setAnchorPoint(ccp(0.0f, 0.0f));
	sideArtL->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() - 1.0f));
	this->addChild(sideArtL, 1);

	CCSprite* sideArtR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	sideArtR->setAnchorPoint(ccp(1.0f, 0.0f));
	sideArtR->setPosition(ccp(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() - 1.0f));
	sideArtR->setFlipX(true);
	this->addChild(sideArtR, 1);


	return true;
}

void LevelBrowserLayer::onNew(CCObject* sender)
{
	GameLevelManager* GLM = GameLevelManager::sharedState();
	// GJGameLevel* newLevel = GLM->createNewLevel();
	GLM->setCreatedNewLevel(true);
	/*CCScene* scene = EditLevelLayer::scene(newLevel);
	CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
	pDirector->replaceScene(fade);*/
}