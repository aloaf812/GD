#include "SavedLevelsLayer.h"
#include "GameManager.h"
USING_NS_CC;

bool SavedLevelsLayer::init()
{
	if (!CCLayer::init())
		return false;

	GameManager::sharedState()->setReturnToSearch(false);
	GameManager::sharedState()->setLastScene(LastGameScene::unk5);
	this->setKeypadEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* bgSprite = CCSprite::create("GJ_gradientBG.png");
	bgSprite->setAnchorPoint(ccp(0.0f, 0.0f));
	this->addChild(bgSprite, -2);

	bgSprite->setScaleX((winSize.width + 10.0f) / bgSprite->getTextureRect().size.width);
	bgSprite->setScaleY((winSize.height + 10.0f) / bgSprite->getTextureRect().size.height);
	bgSprite->setPosition(ccp(-5, -5));
	bgSprite->setColor(ccc3(0, 125, 255));

	CCSprite* cornerArtL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	cornerArtL->setAnchorPoint(ccp(0, 0));
	cornerArtL->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() - 1, CCDirector::sharedDirector()->getScreenBottom() - 1));
	this->addChild(cornerArtL, 1);

	CCSprite* cornerArtR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	cornerArtR->setAnchorPoint(ccp(1, 0));
	cornerArtR->setPosition(ccp(CCDirector::sharedDirector()->getScreenRight() + 1, CCDirector::sharedDirector()->getScreenBottom() - 1));
	cornerArtR->setFlipX(true);
	this->addChild(cornerArtR, 1);

	this->setupLevelBrowser();

	CCSprite* backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backSpr, nullptr, this, menu_selector(SavedLevelsLayer::onBack));
	backBtn->setSizeMult(2.0f);
	CCMenu* backMenu = CCMenu::create(backBtn, 0);
	this->addChild(backMenu, 1);
	backMenu->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() + 24, CCDirector::sharedDirector()->getScreenTop() - 23));

	return true;
}

void SavedLevelsLayer::onBack(cocos2d::CCObject* sender)
{

}

void SavedLevelsLayer::setupLevelBrowser()
{

}