// decompiled by ItzZyann
// from GD 1.71 binary

#include "LevelPage.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
#include "GameManager.h"
#include "GameLevelManager.h"
#include "GameSoundManager.h"
#include "FLAlertLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

LevelPage* LevelPage::create(GJGameLevel* level)
{
	LevelPage* pRet = new LevelPage();
	if (pRet && pRet->init(level))
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

bool LevelPage::init(GJGameLevel* level)
{
	if (!CCLayer::init())
		return false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_level = level;
	m_level->retain();

	// int userCoins = GameStatsManager::sharedState()->getStat("8");
	int reqCoins = m_level->getRequiredCoins();
	bool locked = false;

	m_levelMenu = CCMenu::create();
	this->addChild(m_levelMenu, -1);
	m_levelMenu->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f + 60.0f));

	CCScale9Sprite* button = CCScale9Sprite::create("square02_001.png", CCRect(0, 0, 80, 80));
	button->setOpacity(125);
	button->setContentSize(CCSize(340, 95));

	CCSprite* buttonSpr = CCSprite::create();
	buttonSpr->addChild(button);
	buttonSpr->setContentSize(button->getContentSize());
	button->setPosition(ccp(button->getContentSize().width * 0.5f,
		button->getContentSize().height * 0.5f));

	CCMenuItemSpriteExtra* playExtra = CCMenuItemSpriteExtra::create(
		buttonSpr, NULL, this, menu_selector(LevelPage::onPlay));
	playExtra->setScaleVar(1.1f);
	m_levelMenu->addChild(playExtra);


	// uncomment
	// when dict is complete
	// and some stuffs from user

	if (locked) {
		CCSprite* lockSpr = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
		button->addChild(lockSpr);
		lockSpr->setPosition(ccp(170.0f, 47.5f));

		// int userCoins = GameStatsManager::sharedState()->getStat("8");
		int userCoins = 0;
		CCSprite* coinIcon = CCSprite::createWithSpriteFrameName("GJ_coinsIcon_001.png");
		coinIcon->setScale(1.0f);
		coinIcon->setPosition(ccp(325.0f, 15.0f));

		CCString* coinStr = CCString::createWithFormat("%i/%i", userCoins, reqCoins);
		CCLabelBMFont* coinLabel = CCLabelBMFont::create(coinStr->getCString(), "bigFont.fnt");
		coinLabel->setAnchorPoint(ccp(1.0f, 0.5f));
		coinLabel->setPosition(coinIcon->getPosition() + ccp(-15.0f, 0.5f));
		coinLabel->setScale(0.5f);

		button->addChild(coinIcon);
		button->addChild(coinLabel);
	}
	else {
		CCLabelBMFont* nameLabel = CCLabelBMFont::create(
			m_level->getLevelName().c_str(), "bigFont.fnt");
		nameLabel->setAnchorPoint(ccp(0.0f, 0.5f));
		button->addChild(nameLabel);

		if (nameLabel->getContentSize().width > 250.0f)
			nameLabel->setScale(250.0f / nameLabel->getContentSize().width);
		nameLabel->setScale((std::min)(nameLabel->getScale(), 1.0f));

		int diff = m_level->getDifficulty();
		if (diff <= 0 || diff > 6)
			diff = 0;

		CCString* diffStr = CCString::createWithFormat("diffIcon_%02d_btn_001.png", diff);
		CCSprite* diffSpr = CCSprite::createWithSpriteFrameName(diffStr->getCString());
		button->addChild(diffSpr);
		diffSpr->setScale(1.1f);

		// fix title and diff
		// not position properly
		float diffW = diffSpr->getContentSize().width * diffSpr->getScale();
		float nameW = nameLabel->getContentSize().width * nameLabel->getScale();
		float groupWidth = diffW + nameW + 5.0f + 30.0f;
		float groupLeft = 170.0f - groupWidth * 0.5f;
		diffSpr->setPosition(ccp(groupLeft + diffW * 0.5f, 50.5f));
		nameLabel->setPosition(ccp(diffSpr->getPosition().x + 30.0f, 50.5f));

		if (m_level->getStars() > 0) {
			CCSprite* starIcon = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
			button->addChild(starIcon);
			starIcon->setScale(0.6f);
			starIcon->setPosition(ccp(325.0f, 82.0f));

			CCString* starStr = CCString::createWithFormat("%i", m_level->getStars());
			CCLabelBMFont* starLabel = CCLabelBMFont::create(starStr->getCString(), "bigFont.fnt");
			button->addChild(starLabel);
			starLabel->setAnchorPoint(ccp(1.0f, 0.5f));
			starLabel->setPosition(starIcon->getPosition() + ccp(-12.0f, 0.5f));
			starLabel->setScale(0.5f);

			// if (GameStatsManager::sharedState()->hasCompletedStarLevel(m_level))
			//     starLabel->setColor(ccc3(255, 255, 50));
		}
	}

	// just fixed progress bar
	// god this is just easy fix
	CCSprite* normalBar = CCSprite::create("GJ_progressBar_001.png");
	normalBar->setColor(ccBLACK);
	normalBar->setOpacity(125);
	normalBar->setScale(1.0f);
	this->addChild(normalBar, 3);
	normalBar->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f - 30.0f));

	CCSprite* normalFill = CCSprite::create("GJ_progressBar_001.png");
	normalFill->setScaleX(0.992f);
	normalFill->setScaleY(0.86f);
	normalFill->setColor(ccGREEN);
	normalBar->addChild(normalFill, 1);
	normalFill->setAnchorPoint(ccp(0.0f, 0.5f));
	{
		float barW = normalFill->getContentSize().width;
		float offsetX = (barW - barW * 0.992f) * 0.5f;
		normalFill->setPosition(ccp(offsetX, normalBar->getContentSize().height * 0.5f));

		float pct = (float)m_level->getNormalPercent() / 100.0f;
		float fillW = barW * pct;
		if (fillW > barW) fillW = barW;
		normalFill->setTextureRect(CCRect(0, 0, fillW, normalFill->getContentSize().height));
	}

	CCSprite* practiceBar = CCSprite::create("GJ_progressBar_001.png");
	practiceBar->setColor(ccBLACK);
	practiceBar->setOpacity(125);
	practiceBar->setScale(1.0f);
	this->addChild(practiceBar, 3);
	practiceBar->setPosition(normalBar->getPosition() + ccp(0.0f, -50.0f));

	CCSprite* practiceFill = CCSprite::create("GJ_progressBar_001.png");
	practiceFill->setScaleX(0.992f);
	practiceFill->setScaleY(0.86f);
	practiceFill->setColor(ccc3(0, 255, 255));
	practiceBar->addChild(practiceFill, 1);
	practiceFill->setAnchorPoint(ccp(0.0f, 0.5f));
	{
		practiceFill->setPosition(normalFill->getPosition());

		float barW = practiceFill->getContentSize().width;
		float pct = (float)m_level->getPracticePercent() / 100.0f;
		float fillW = barW * pct;
		if (fillW > barW) fillW = barW;
		practiceFill->setTextureRect(CCRect(0, 0, fillW, practiceFill->getContentSize().height));
	}

	CCLabelBMFont* normalPct = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", m_level->getNormalPercent())->getCString(),
		"bigFont.fnt");
	this->addChild(normalPct, 4);
	normalPct->setPosition(normalBar->getPosition());
	normalPct->setScale(0.5f);

	CCLabelBMFont* practicePct = CCLabelBMFont::create(
		CCString::createWithFormat("%i%%", m_level->getPracticePercent())->getCString(),
		"bigFont.fnt");
	this->addChild(practicePct, 4);
	practicePct->setPosition(practiceBar->getPosition());
	practicePct->setScale(0.5f);

	CCLabelBMFont* normalLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
	this->addChild(normalLabel, 4);
	normalLabel->setPosition(normalBar->getPosition() + ccp(0.0f, 20.0f));
	normalLabel->setScale(0.5f);

	CCLabelBMFont* practiceLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
	this->addChild(practiceLabel, 4);
	practiceLabel->setPosition(practiceBar->getPosition() + ccp(0.0f, 20.0f));
	practiceLabel->setScale(0.5f);

	int coinCount = m_level->getCoins();
	if (coinCount > 0 && !locked) {
		CCPoint basePos(324.0f, 16.0f);
		for (int i = 1; i <= coinCount; i++) {

			// bool hasCoin = GameStatsManager::sharedState()->hasUniqueItem(m_level->getCoinKey(i));
			bool hasCoin = false;
			const char* icon = hasCoin
				? "GJ_coinsIcon_001.png"
				: "GJ_coinsIcon_gray_001.png";

			CCSprite* coin = CCSprite::createWithSpriteFrameName(icon);
			button->addChild(coin);
			coin->setScale(1.0f);
			coin->setPosition(basePos + ccp((float)(coinCount - i) * -26.0f, 0.0f));

			if (!hasCoin)
				coin->setColor(ccc3(225, 225, 225));
		}
	}

	return true;
}

void LevelPage::onInfo(cocos2d::CCObject* sender) {
	cocos2d::CCString* text = cocos2d::CCString::createWithFormat(
		"<cy>%s</c>\n"
		"<cg>Total Attempts</c>: %i\n"
		"<cl>Total Jumps</c>: %i\n"
		"<cp>Normal</c>: %i%%\n"
		"<co>Practice</c>: %i%%",
			m_level->getLevelName().c_str(),
			m_level->getAttempts(),
			m_level->getJumps(),
			m_level->getNormalPercent(),
			m_level->getPracticePercent()
		);

	FLAlertLayer::create(
		nullptr, "Level Stats", text->getCString(),
		"OK", nullptr,
		300.0f)->show();
}

void LevelPage::onPlay(cocos2d::CCObject* sender)
{
	SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
	SAE->stopBackgroundMusic();

	GameSoundManager* GSoundM = GameSoundManager::sharedManager();
	GSoundM->playEffect("playSound_01.ogg", 1.0f, 0.0f, 0.3f);

	GameManager* pGameManager = GameManager::sharedState();
	pGameManager->setLastScene(LastGameScene::LevelSelect);

	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene* pScene = PlayLayer::scene(m_level);
	CCTransitionFade* fade = CCTransitionFade::create(0.5f, pScene);
	pDirector->replaceScene(fade);
}