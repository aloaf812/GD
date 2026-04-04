// this class is pure spaghetti code but it somehow works
#include "MenuGameLayer.h"
#include "GameManager.h"
#include "AppDelegate.h"
#include <cmath>
USING_NS_CC;

MenuGameLayer::MenuGameLayer() {
    PlayerObject* m_playerObject = nullptr;
    m_backgroundSprite = nullptr;
    m_groundSprite = nullptr;
    m_backgroundSpeed = 0.0f;
    m_bgOffset = 0.0f;
    m_groundOffset = 0.0f;
    m_bgWidth = 0.0f;
    m_groundWidth = 0.0f;
}

bool MenuGameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    GameManager* pGameManager = GameManager::sharedState();
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();

    m_backgroundSprite = CCSprite::create(pGameManager->getBGTexture(pGameManager->getLoadedBGIdx()));
    m_backgroundSprite->setAnchorPoint(ccp(0, 0));
    m_backgroundSprite->setScale(pDirector->getScreenScaleFactorMax());
    m_backgroundSprite->setColor(ccc3(0, 102, 255));
    ccTexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    m_backgroundSprite->getTexture()->setTexParameters(&texParams);
    m_backgroundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_backgroundSprite->getContentSize().height));
    this->addChild(m_backgroundSprite, -1);
    m_bgWidth = winSize.width;
    
    // ground
    m_groundLayer = CCLayer::create();
    this->addChild(m_groundLayer, 3);
    
    m_groundSprite = CCSprite::create(pGameManager->getGTexture(1));
    m_groundSprite->getTexture()->setTexParameters(&texParams);
    m_groundLayer->addChild(m_groundSprite, 2);
    m_groundSprite->setAnchorPoint(ccp(0, 1));
   	m_groundSprite->setColor(ccc3(0, 102, 255));
    m_groundSprite->setPosition(ccp(0.0f, 90.0f));
	m_groundSprite->setTextureRect(CCRectMake(0, 0, winSize.width * 2, m_groundSprite->getContentSize().height));
    
    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, 90.0f));
    m_groundLayer->addChild(leftShadow, 3);
    leftShadow->setOpacity(100);
    leftShadow->setColor(ccc3(150, 150, 150));
	ccBlendFunc sBlendFunc = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	leftShadow->setBlendFunc(sBlendFunc);
    leftShadow->setTag(0);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, 90.0f));
    rightShadow->setFlipX(true);
    m_groundLayer->addChild(rightShadow, 3);
    rightShadow->setOpacity(100);
    rightShadow->setColor(ccc3(150, 150, 150));
    rightShadow->setBlendFunc(sBlendFunc);
    rightShadow->setTag(0);
    
    // the line looks odd but it works
    CCSprite* lineSprite = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    m_groundLayer->addChild(lineSprite, 3);
    lineSprite->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 90.0f));
    
#pragma region Player
	/*int cube = ceilf((rand() * 4.6566e-10) * 37.0);
	int ship = ceilf((rand() * 4.6566e-10) * 13.0);*/

	int cube = rand() % 37;
	int ship = rand() % 13;

	int tmpStreak = pGameManager->getPlayerStreak();
	pGameManager->setPlayerStreak(1);
	this->m_playerObject = PlayerObject::create((cube + 1), (ship + 1), this);
	this->addChild(m_playerObject, 0);

	m_playerObject->setPosition(ccp(0.0f, 105.0f));

	// ccColor3B firstColor = pGameManager->colorForIdx(rand() * 4.656613e-10 * 18.0);
	ccColor3B firstColor = pGameManager->colorForIdx(rand() % 18);
	m_playerObject->setColor(firstColor);
	// ccColor3B secondColor = pGameManager->colorForIdx(rand() * 4.656613e-10 * 18.0);
	ccColor3B secondColor = pGameManager->colorForIdx(rand() % 18);
	m_playerObject->setSecondColor(secondColor);
	pGameManager->setPlayerStreak(tmpStreak);
#pragma endregion

    scheduleUpdate();
    // this->schedule(schedule_selector(MenuGameLayer::tryJump), 0.25f);
    
    return true;
}

void MenuGameLayer::update(float delta)
{
    float step = delta * 60.0f;

	m_playerObject->setLastP(m_playerObject->getPosition());
	m_playerObject->update(step);
    
	if (m_playerObject->getFlyMode())
		m_playerObject->updateShipRotation(step);

    /*float bgSpeed = 5.77f * 0.1f;
    float groundSpeed = 5.77f * 0.9f;
    
    m_bgOffset += step * bgSpeed;
    m_groundOffset += step * groundSpeed;
    
    if (m_bgOffset > m_bgWidth){
        m_bgOffset -= m_bgWidth;
        }
    if (m_groundOffset > m_groundWidth){
        m_groundOffset -= m_groundWidth;
    }

    m_backgroundSprite->setTextureRect(CCRectMake(m_bgOffset, 0, m_bgWidth * 2, m_backgroundSprite->getContentSize().height));
    m_groundSprite->setTextureRect(CCRectMake(m_groundOffset, 0, m_bgWidth * 2, 90.0f));*/

}