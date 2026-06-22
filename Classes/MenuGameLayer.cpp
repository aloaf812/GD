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
    
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();

    // ground
    m_groundLayer = CCLayer::create();
    this->addChild(m_groundLayer, 3);

    GameManager* pGameManager = GameManager::sharedState();

    m_bgSprite = CCSprite::create(pGameManager->getBGTexture(pGameManager->getLoadedBGIdx()));
    ccTexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    m_bgSprite->getTexture()->setTexParameters(&texParams);
    this->addChild(m_bgSprite, -1);
    m_bgSprite->setAnchorPoint(ccp(0, 0));
    m_bgSprite->setScale(pDirector->getScreenScaleFactorMax());
	m_bgSprite->setColor(ccc3(0, 102, 255));	
    m_bgSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_bgSprite->getContentSize().height));
    
    m_groundSprite = CCSprite::create(pGameManager->getGTexture(1));
    m_groundSprite->getTexture()->setTexParameters(&texParams);
    m_groundLayer->addChild(m_groundSprite, 2);
    m_groundSprite->setAnchorPoint(ccp(0, 1));
   	m_groundSprite->setColor(ccc3(0, 102, 255));
    m_groundSprite->setPosition(ccp(0.0f, 90.0f));
	m_groundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_groundSprite->getContentSize().height));
    
    CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    m_groundLayer->addChild(lineSprite, 3);
    lineSprite->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 90.0f));
	lineSprite->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
	lineSprite->setOpacity(200);

    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, 90.0f));
    m_groundLayer->addChild(leftShadow, 3);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, 90.0f));
    m_groundLayer->addChild(rightShadow, 3);
    rightShadow->setFlipX(true);

    leftShadow->setOpacity(100);
    rightShadow->setOpacity(100);

	leftShadow->setScaleX(0.7f);
	rightShadow->setScaleX(0.7f);
	
	ccBlendFunc sBlendFunc = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	leftShadow->setBlendFunc(sBlendFunc);
    rightShadow->setBlendFunc(sBlendFunc);

#pragma region Player
	float cube = ceilf(CCRANDOM_0_1() * 37.0);
	float ship = ceilf(CCRANDOM_0_1() * 13.0);

	int tmpStreak = pGameManager->getPlayerStreak();
	pGameManager->setPlayerStreak(1);
	m_playerObject = PlayerObject::create((cube + 1), (ship + 1), this);
	this->addChild(m_playerObject, 0);

	m_playerObject->setPosition(ccp(0.0f, 105.0f));

	ccColor3B firstColor = pGameManager->colorForIdx(CCRANDOM_0_1() * 18);
	m_playerObject->setColor(firstColor);

	ccColor3B secondColor = pGameManager->colorForIdx(CCRANDOM_0_1() * 18);
	m_playerObject->setSecondColor(secondColor);
	pGameManager->setPlayerStreak(tmpStreak);
#pragma endregion

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
		balancer = (playerScale * 30.0f) * 0.5f;

	float groundYPos = pDirector->getScreenBottom();
	if (m_playerObject->getPosition().y > (groundYPos + 90 + 15 - balancer)) {
		m_playerObject->setPosition(m_playerObject->getPosition());
		m_playerObject->hitGround(false);
	}

	if (winSize.width + 100 < m_playerObject->getPosition().x) {
		m_playerObject->deactivateStreak();
		
		m_playerObject->setPosition(ccp(-100 + (CCRANDOM_0_1() * 5) * 100, m_playerObject->getPosition().y));
		m_playerObject->setColor(GAME_MANAGER->colorForIdx(CCRANDOM_0_1() * 18));

	}
	// unfinished chunk here

	// i redid my math what do you guys think

	m_backgroundPosition = m_backgroundPosition + ccp(step * 5.77 * 0.9, 0.0f);
	CCPoint newBGPos = m_backgroundPosition * 0.1;

	int i;
	for (i = newBGPos.x; i < -m_bgSpeed; i = i + m_bgSpeed)
		newBGPos.x += m_bgSpeed;

	m_bgSprite->setPosition(newBGPos);

	CCPoint newGPos = ccp(m_backgroundPosition.x,
		pDirector->getScreenBottom() + 90.0);

	for (i = newGPos.x; i < -m_groundSpeed; i = i + m_groundSpeed)
		newGPos.x += m_groundSpeed;

	m_groundSprite->setPosition(newGPos);
}

void MenuGameLayer::tryJump(float dt)
{
	// unfinishedddddd

	if (!m_playerObject->getFlyMode()) {
		if (m_playerObject->getRollMode()) {
		
		}

		if (!m_playerObject->getBirdMode())
		{

		}

	}
	
	m_playerObject->pushButton(PlayerButton::Jump);
}