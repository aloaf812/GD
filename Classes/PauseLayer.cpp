#include "PauseLayer.h"
#include "GameManager.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "GameSoundManager.h"
#include "LevelEditorLayer.h"
#include "TutorialLayer.h"

#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

void PauseLayer::customSetup()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	CCScale9Sprite* background = CCScale9Sprite::create("square04_001.png", CCRect(0, 0, 80, 80));
	background->setOpacity(175);

	float bgWidth = (pDirector->getScreenRight() - 20.0f) - pDirector->getScreenLeft();
	float bgHeight = (pDirector->getScreenTop() - 20.0f) - pDirector->getScreenBottom();

	background->setContentSize(CCSize(bgWidth, bgHeight));
	background->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	background->setColor(ccBLACK);
	this->addChild(background);

	std::string levelName = PLAY_LAYER->getLevel()->getLevelName(); 
	CCLabelBMFont* levelLabel = CCLabelBMFont::create(levelName.c_str(), "bigFont.fnt");
	levelLabel->setPosition(ccp(winSize.width * 0.5f, bgHeight - 20.0f));
	this->addChild(levelLabel);

	CCMenu* mainButtonMenu = CCMenu::create();
	this->addChild(mainButtonMenu);

	CCSprite* menuBtn = CCSprite::createWithSpriteFrameName("GJ_menuBtn_001.png");

	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel) {
		CCSprite* editBtn = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
		editBtn->setScale(menuBtn->getContentSize().width / editBtn->getContentSize().height);
		CCMenuItemSpriteExtra* editExtra = CCMenuItemSpriteExtra::create(editBtn, NULL, this, menu_selector(PauseLayer::onEdit));
		mainButtonMenu->addChild(editExtra);
	}

	CCSprite* practiceBtn;
	SEL_MenuHandler practiceCallback;
	if (!PLAY_LAYER->getPracticeMode()) {
		practiceBtn = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
		practiceCallback = menu_selector(PauseLayer::onPracticeMode);
	}
	else {
		practiceBtn = CCSprite::createWithSpriteFrameName("GJ_normalBtn_001.png");
		practiceCallback = menu_selector(PauseLayer::onNormalMode);
	}
	CCMenuItemSpriteExtra* practiceExtra = CCMenuItemSpriteExtra::create(practiceBtn, NULL, this, practiceCallback);
	mainButtonMenu->addChild(practiceExtra);

	CCSprite* resumeBtn = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
	CCMenuItemSpriteExtra* resumeExtra = CCMenuItemSpriteExtra::create(resumeBtn, NULL, this, menu_selector(PauseLayer::onResume));
	mainButtonMenu->addChild(resumeExtra);

	CCMenuItemSpriteExtra* menuExtra = CCMenuItemSpriteExtra::create(menuBtn, NULL, this, menu_selector(PauseLayer::onQuit));
	mainButtonMenu->addChild(menuExtra);

	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel) {
		CCSprite* restartBtn = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
		CCMenuItemSpriteExtra* restartExtra = CCMenuItemSpriteExtra::create(restartBtn, NULL, this, menu_selector(PauseLayer::onRestart));
		mainButtonMenu->addChild(restartExtra);
	}

	mainButtonMenu->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f));

	float spacing;
	if (PLAY_LAYER->getLevel()->getLevelType() == GJLevelType::LocalLevel)
		spacing = 15.0f;
	else
		spacing = 20.0f;

	mainButtonMenu->alignItemsHorizontallyWithPadding(spacing);

}

void PauseLayer::onResume(CCObject* sender)
{
	PLAY_LAYER->resume();
	CCNode::removeMeAndCleanup();	
}

void PauseLayer::onQuit(CCObject* sender)
{
	this->unscheduleAllSelectors();
	PLAY_LAYER->resume();
	PLAY_LAYER->onQuit();
	GameSoundManager::sharedManager()->playEffect("quitSound_01.ogg", 1.0f, 0.0f, 0.7f);
}

void PauseLayer::onEdit(CCObject* sender)
{
	PLAY_LAYER->resume();
	PLAY_LAYER->stopAllActions();
	PLAY_LAYER->unscheduleAllSelectors();

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);

	CCScene* scene = LevelEditorLayer::scene(PLAY_LAYER->getLevel());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
}

void PauseLayer::onFX(CCObject* sender)
{
	GameManager::sharedState()->toggleFX();
}

void PauseLayer::onMusic(CCObject* sender)
{
	GameManager::sharedState()->toggleMusic();
}

void PauseLayer::onNormalMode(CCObject* sender)
{
	PLAY_LAYER->togglePracticeMode(false);
	this->onResume(nullptr);
}

void PauseLayer::onPracticeMode(CCObject* sender)
{
	GameManager::sharedState()->setClickedPractice(true);
	PLAY_LAYER->togglePracticeMode(true);
	this->onResume(nullptr);
}

void PauseLayer::onRestart(CCObject* sender)
{
	PLAY_LAYER->resumeAndRestart();
	CCNode::removeMeAndCleanup();
}

void PauseLayer::onHelp(CCObject* sender)
{
	TutorialLayer::create()->show();
}