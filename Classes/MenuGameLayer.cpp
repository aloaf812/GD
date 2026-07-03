// this class is pure spaghetti code but it somehow works
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
    if ( !CCLayer::init() )
        return false;
    
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // ground
    m_groundLayer = CCLayer::create();
    this->addChild(m_groundLayer, 3);

	m_bgSprite = CCSprite::create(GameManager::sharedState()->getBGTexture(GameManager::sharedState()->getLoadedBGIdx()));
    ccTexParams bgTexParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    m_bgSprite->getTexture()->setTexParameters(&bgTexParams);
    this->addChild(m_bgSprite, -1);
    m_bgSprite->setAnchorPoint(ccp(0, 0));
	m_bgSprite->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());

	// HE DOES THE SAME THING HERE WHATTTTTTT
	ccColor3B color1 = ccc3(0, 102, 255);
	m_bgSprite->setColor(ccc3(40, 125, 255));
	m_bgSprite->setColor(color1);
    
	CCRect bgTexRect = m_bgSprite->getTextureRect();
	m_bgSpeed = bgTexRect.size.width * m_bgSprite->getScale();
	bgTexRect.size.width = bgTexRect.size.width * 2.0f;
	m_bgSprite->setTextureRect(bgTexRect);
    
#pragma region Ground
	char const* gIdx = GameManager::sharedState()->getGTexture(GameManager::sharedState()->getLoadedGIdx());
	m_groundSprite = CCSprite::create(gIdx);
	ccTexParams gTexParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    m_groundSprite->getTexture()->setTexParameters(&gTexParams);
    m_groundLayer->addChild(m_groundSprite, 2);
    m_groundSprite->setAnchorPoint(ccp(0, 1));
	m_groundSprite->setScale(CCDirector::sharedDirector()->getScreenScaleFactorMax());
	m_groundSprite->setColor(ccc3(color1.r * 0.8f, color1.g * 0.8f, color1.b * 0.8f));

	CCRect gTexRect = m_groundSprite->getTextureRect();
	m_groundSpeed = gTexRect.size.width * m_groundSprite->getScale();
	int gBalancer = ceil(winSize.width / gTexRect.size.height) + 1; // idk if this is the right name to give the var
	gTexRect.size.width = gTexRect.size.height * gBalancer;
	m_groundSprite->setTextureRect(gTexRect);
	m_groundSprite->setPosition(ccp(0.0f, CCDirector::sharedDirector()->getScreenBottom() + 90.0f));
    
    CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    m_groundLayer->addChild(lineSprite, 3);
	lineSprite->setPosition(ccp(winSize.width * 0.5f, CCDirector::sharedDirector()->getScreenBottom() + 90.0f));
	ccBlendFunc lineBlendFunc = { GL_SRC_ALPHA, GL_ONE };
	lineSprite->setBlendFunc(lineBlendFunc);
	lineSprite->setOpacity(200);

    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
	leftShadow->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() - 1.0f, CCDirector::sharedDirector()->getScreenBottom() + 90.0f));
    m_groundLayer->addChild(leftShadow, 3);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
	rightShadow->setPosition(ccp(CCDirector::sharedDirector()->getScreenRight() + 1.0f, CCDirector::sharedDirector()->getScreenBottom() + 90.0f));
    m_groundLayer->addChild(rightShadow, 3);
    rightShadow->setFlipX(true);

    leftShadow->setOpacity(100);
    rightShadow->setOpacity(100);

	leftShadow->setScaleX(0.7f);
	rightShadow->setScaleX(0.7f);
	
	ccBlendFunc sBlendFunc = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	leftShadow->setBlendFunc(sBlendFunc);
    rightShadow->setBlendFunc(sBlendFunc);
#pragma endregion

#pragma region Player
	float cube = ceilf(CCRANDOM_0_1() * 37.0);
	float ship = ceilf(CCRANDOM_0_1() * 13.0);

	int tmpStreak = GameManager::sharedState()->getPlayerStreak();
	GameManager::sharedState()->setPlayerStreak(1);
	m_playerObject = PlayerObject::create((cube + 1), (ship + 1), this);
	this->addChild(m_playerObject, 0);

	m_playerObject->setPosition(ccp(0.0f, 105.0f));

	m_playerObject->setColor(GameManager::sharedState()->colorForIdx(CCRANDOM_0_1() * 18));
	m_playerObject->setSecondColor(GameManager::sharedState()->colorForIdx(CCRANDOM_0_1() * 18));

	GameManager::sharedState()->setPlayerStreak(tmpStreak);
#pragma endregion

    scheduleUpdate();
	this->schedule(schedule_selector(MenuGameLayer::tryJump), 0.25f);
    
    return true;
}

void MenuGameLayer::update(float delta)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

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

	float groundY = CCDirector::sharedDirector()->getScreenBottom() + 90.0f + 15.0f - balancer;
	if (m_playerObject->getPosition().y < groundY)
	{
		m_playerObject->setPosition(ccp(m_playerObject->getPosition().x, groundY));
		m_playerObject->hitGround(false);
	}

	if (m_playerObject->getPosition().x > winSize.width + 100.0f)
	{
		m_playerObject->deactivateStreak();

		m_playerObject->setPosition(ccp(-100.0f - (CCRANDOM_0_1() * 5.0f * 100.0f), m_playerObject->getPosition().y));

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

	m_backgroundPosition = ccp(m_backgroundPosition.x + (step * 5.77f) * 0.9f, 0.0f);
	CCPoint newBGPos = ccp(-m_backgroundPosition.x * 0.1f, -m_backgroundPosition.y * 0.1f);
	float i;
	for (i = newBGPos.x; i < -m_bgSpeed; i += m_bgSpeed);
	newBGPos.x = i;
	m_bgSprite->setPosition(newBGPos);

	CCPoint groundPos = ccp(m_backgroundPosition.x, CCDirector::sharedDirector()->getScreenBottom() + 90.0f);
	for (i = groundPos.x; i < -m_groundSpeed; i += m_groundSpeed);
	groundPos.x = i;
	m_groundSprite->setPosition(groundPos);

}

void MenuGameLayer::tryJump(float dt)
{
	float jumpChance;

	if (m_playerObject->getFlyMode())
	{
		bool belowCeiling = m_playerObject->getPosition().y < CCDirector::sharedDirector()->getScreenBottom() + 90.0f + 15.0f + 100.0f;
		jumpChance = belowCeiling ? 0.3f : 0.0f;
	}
	else if (m_playerObject->getRollMode())
	{
		jumpChance = -1.0f;
	}
	else if (m_playerObject->getBirdMode())
	{
		bool belowCeiling = m_playerObject->getPosition().y < CCDirector::sharedDirector()->getScreenBottom() + 90.0f + 15.0f + 200.0f;
		jumpChance = belowCeiling ? 0.4f : 0.0f;
	}
	else
	{
		jumpChance = 0.2f;
	}

	if (CCRANDOM_0_1() <= jumpChance
		&& (m_playerObject->getOnGround() || m_playerObject->isFlying()))
	{
		m_playerObject->pushButton(PlayerButton::Jump);
	}
	else
	{
		m_playerObject->releaseButton(PlayerButton::Jump);
	}
}