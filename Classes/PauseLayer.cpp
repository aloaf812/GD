#include "PauseLayer.h"
#include "GameManager.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "GameSoundManager.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

void PauseLayer::customSetup()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCScale9Sprite* background = CCScale9Sprite::create("square04_001.png", CCRect(0, 0, 80, 80));
	background->setOpacity(175);

	float bgWidth = (pDirector->getScreenRight() - 20.0f) - pDirector->getScreenLeft();
	float bgHeight = (pDirector->getScreenTop() - 20.0f) - pDirector->getScreenBottom();

	background->setContentSize({ bgWidth, bgHeight });
	background->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	background->setColor(ccBLACK);
	this->addChild(background);

	std::string levelName = PLAY_LAYER->getLevel()->getLevelName(); 
	CCLabelBMFont* levelLabel = CCLabelBMFont::create(levelName.c_str(), "bigFont.fnt");
	levelLabel->setPosition(ccp(winSize.width * 0.5f, bgHeight - 20.0f));
	this->addChild(levelLabel);

	CCMenu* mainButtonMenu = CCMenu::create();

	// uses if statement to check if in practice
	CCSprite* practiceBtn = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
	CCMenuItemSpriteExtra* practiceExtra = CCMenuItemSpriteExtra::create(practiceBtn, NULL, this, menu_selector(PauseLayer::onResume));
	mainButtonMenu->addChild(practiceExtra);

	CCSprite* resumeBtn = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
	CCMenuItemSpriteExtra* resumeExtra = CCMenuItemSpriteExtra::create(resumeBtn, NULL, this, menu_selector(PauseLayer::onResume));
	mainButtonMenu->addChild(resumeExtra);

	CCSprite* menuBtn = CCSprite::createWithSpriteFrameName("GJ_menuBtn_001.png");
	CCMenuItemSpriteExtra* menuExtra = CCMenuItemSpriteExtra::create(menuBtn, NULL, this, menu_selector(PauseLayer::onQuit));
	mainButtonMenu->addChild(menuExtra);

	mainButtonMenu->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f));
	mainButtonMenu->alignItemsHorizontallyWithPadding(20.0f);
	this->addChild(mainButtonMenu);
}

void PauseLayer::onResume(CCObject* sender)
{
	PLAY_LAYER->resume();
	dynamic_cast<CCNode*>(sender)->removeMeAndCleanup();	
}

void PauseLayer::onQuit(CCObject* sender)
{
	this->unscheduleAllSelectors();
	PLAY_LAYER->resume();
	PLAY_LAYER->onQuit();
	GameSoundManager::sharedManager()->playEffect("quitSound_01.ogg", 1.0f, 0.0f, 0.7f);
}