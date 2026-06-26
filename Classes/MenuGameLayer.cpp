// decompiled by ItzZyann
// from GD 1.71 binary

#include "MenuGameLayer.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include <cmath>
USING_NS_CC;

MenuGameLayer::MenuGameLayer()
{
	m_playerObject = nullptr;
	m_bgSprite = nullptr;
	m_groundSprite = nullptr;
	m_groundLayer = nullptr;
	m_groundSpeed = 0.0f;
	m_bgSpeed = 0.0f;
}

MenuGameLayer* MenuGameLayer::create()
{
	MenuGameLayer *pRet = new MenuGameLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool MenuGameLayer::init()
{
	if (!CCLayer::init())
		return false;

	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	m_groundLayer = CCLayer::create();
	this->addChild(m_groundLayer, 3);

	GameManager* pGameManager = GameManager::sharedState();

	m_bgSprite = CCSprite::create(pGameManager->getBGTexture(pGameManager->getLoadedBGIdx()));
	ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	m_bgSprite->getTexture()->setTexParameters(&texParams);
	this->addChild(m_bgSprite, -1);
	m_bgSprite->setAnchorPoint(ccp(0.0f, 0.0f));
	m_bgSprite->setScale(pDirector->getScreenScaleFactorMax());
	m_bgSprite->setColor(ccc3(0, 102, 255));

	CCRect bgTexRect = m_bgSprite->getTextureRect();
	m_bgSpeed = bgTexRect.size.width * m_bgSprite->getScale();
	float bgDoubleW = m_bgSpeed * 2.0f;
	m_bgSprite->setTextureRect(CCRectMake(0, 0, bgDoubleW, bgTexRect.size.height));

	// Initialize Ground
	m_groundSprite = CCSprite::create(pGameManager->getGTexture(1));
	m_groundSprite->getTexture()->setTexParameters(&texParams);
	m_groundLayer->addChild(m_groundSprite, 2);
	m_groundSprite->setAnchorPoint(ccp(0.0f, 1.0f));
	m_groundSprite->setColor(ccc3(0, 102, 255));

	CCRect gTexRect = m_groundSprite->getTextureRect();
	m_groundSpeed = gTexRect.size.width * pDirector->getScreenScaleFactorMax();
	m_groundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2.0f, gTexRect.size.height));
	m_groundSprite->setPosition(ccp(0.0f, pDirector->getScreenBottom() + 90.0f));

	CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
	m_groundLayer->addChild(lineSprite, 3);
	lineSprite->setPosition(ccp(winSize.width * 0.5f, pDirector->getScreenBottom() + 90.0f));
	lineSprite->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
	lineSprite->setOpacity(200);

	CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
	leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
	leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() + 90.0f));
	m_groundLayer->addChild(leftShadow, 3);

	CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
	rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
	rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() + 90.0f));
	m_groundLayer->addChild(rightShadow, 3);
	rightShadow->setFlipX(true);

	leftShadow->setOpacity(100);
	rightShadow->setOpacity(100);

	leftShadow->setScaleX(0.7f);
	rightShadow->setScaleX(0.7f);

	ccBlendFunc sBlendFunc = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	leftShadow->setBlendFunc(sBlendFunc);
	rightShadow->setBlendFunc(sBlendFunc);

	float cube = ceilf(CCRANDOM_0_1() * 37.0f);
	float ship = ceilf(CCRANDOM_0_1() * 13.0f);

	int tmpStreak = pGameManager->getPlayerStreak();
	pGameManager->setPlayerStreak(1);
	m_playerObject = PlayerObject::create((int)(cube + 1.0f), (int)(ship + 1.0f), this);
	this->addChild(m_playerObject, 0);

	m_playerObject->setPosition(ccp(0.0f, 105.0f));

	ccColor3B firstColor = pGameManager->colorForIdx((int)(CCRANDOM_0_1() * 18.0f));
	m_playerObject->setColor(firstColor);

	ccColor3B secondColor = pGameManager->colorForIdx((int)(CCRANDOM_0_1() * 18.0f));
	m_playerObject->setSecondColor(secondColor);
	pGameManager->setPlayerStreak(tmpStreak);

	scheduleUpdate();
	this->schedule(schedule_selector(MenuGameLayer::tryJump), 0.25f);

	return true;
}

void MenuGameLayer::update(float delta)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize winSize = pDirector->getWinSize();

	float step = delta * 60.0f;

	m_playerObject->setLastP(m_playerObject->getPosition());
	m_playerObject->update(step);

	if (m_playerObject->getFlyMode())
		m_playerObject->updateShipRotation(step);

	float balancer;
	float playerScale = m_playerObject->getPlayerScale();
	if (playerScale == 1.0f)
		balancer = 0.0f;
	else
		balancer = ((1.0f - playerScale) * 30.0f) * 0.5f;

	float groundY = pDirector->getScreenBottom() + 90.0f + 15.0f - balancer;
	if (m_playerObject->getPosition().y < groundY)
	{
		m_playerObject->setPosition(ccp(m_playerObject->getPosition().x, groundY));
		m_playerObject->hitGround(false);
	}

	if (m_playerObject->getPosition().x > winSize.width + 100.0f)
	{
		m_playerObject->deactivateStreak();

		float newX = -100.0f - (CCRANDOM_0_1() * 5.0f * 100.0f);
		m_playerObject->setPosition(ccp(newX, m_playerObject->getPosition().y));

		m_playerObject->setColor(GameManager::sharedState()->colorForIdx((int)(CCRANDOM_0_1() * 18.0f)));
		m_playerObject->setSecondColor(GameManager::sharedState()->colorForIdx((int)(CCRANDOM_0_1() * 18.0f)));

		m_playerObject->updatePlayerFrame((int)roundf(CCRANDOM_0_1() * 38.0f));
		m_playerObject->update(0);

		if (CCRANDOM_0_1() < 0.2f && !m_playerObject->getFlyMode())
		{
			m_playerObject->toggleFlyMode(true);
			m_playerObject->updatePlayerShipFrame((int)roundf(CCRANDOM_0_1() * 14.0f));
		}
		else if (CCRANDOM_0_1() < 0.4f && !m_playerObject->getRollMode())
		{
			m_playerObject->toggleRollMode(true);
			m_playerObject->updatePlayerRollFrame((int)roundf(CCRANDOM_0_1() * 7.0f));
		}
		else if (CCRANDOM_0_1() < 0.6f && !m_playerObject->getBirdMode())
		{
			m_playerObject->toggleBirdMode(true);
			m_playerObject->updatePlayerBirdFrame((int)roundf(CCRANDOM_0_1() * 7.0f));
		}
		else
		{
			m_playerObject->toggleFlyMode(false);
			m_playerObject->toggleRollMode(false);
			m_playerObject->toggleBirdMode(false);
		}

		m_playerObject->updateGlowColor();
	}

	m_backgroundPosition.x -= step * 5.193f;

	float bgTileW = m_bgSprite->getTexture()->getContentSizeInPixels().width;
	float bgX = fmodf(m_backgroundPosition.x * 0.1f, bgTileW);
	if (bgX > 0) bgX -= bgTileW;
	m_bgSprite->setPosition(ccp(bgX, 0.0f));

	float gX = fmodf(m_backgroundPosition.x, winSize.width);
	if (gX > 0) gX -= winSize.width;
	m_groundSprite->setPosition(ccp(gX, pDirector->getScreenBottom() + 90.0f));
}

void MenuGameLayer::tryJump(float dt)
{
	auto pDirector = CCDirector::sharedDirector();
	float jumpChance;

	if (m_playerObject->getFlyMode())
	{
		float shipCeiling = pDirector->getScreenBottom() + 90.0f + 15.0f + 100.0f;
		bool belowCeiling = m_playerObject->getPosition().y < shipCeiling;
		jumpChance = belowCeiling ? 0.3f : 0.0f;
	}
	else if (m_playerObject->getRollMode())
	{
		jumpChance = -1.0f;
	}
	else if (m_playerObject->getBirdMode())
	{
		float ufoCeiling = pDirector->getScreenBottom() + 90.0f + 15.0f + 200.0f;
		bool belowCeiling = m_playerObject->getPosition().y < ufoCeiling;
		jumpChance = belowCeiling ? 0.4f : 0.0f;
	}
	else
	{
		jumpChance = 0.2f;
	}

	if (CCRANDOM_0_1() <= jumpChance
		&& (m_playerObject->canJump() || m_playerObject->isFlying()))
	{
		m_playerObject->pushButton(PlayerButton::Jump);
	}
	else
	{
		m_playerObject->releaseButton(PlayerButton::Jump);
	}
}