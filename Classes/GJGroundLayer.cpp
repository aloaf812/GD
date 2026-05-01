#include "GJGroundLayer.h"
#include "GameManager.h"
#include <cmath>
USING_NS_CC;

GJGroundLayer::GJGroundLayer()
{
	this->m_groundWidth = 0.0f;
	this->m_groundSprite = NULL;
	this->m_line = NULL;
	this->m_isActive = false;
}

GJGroundLayer* GJGroundLayer::create(int gID)
{
	GJGroundLayer *pRet = new GJGroundLayer();
	if (pRet && pRet->init(gID))
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

bool GJGroundLayer::init(int gID)
{
	if (!CCLayer::init())
    	return false;

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    GameManager* pGameManager = GameManager::sharedState();

   	m_groundSprite = CCSprite::create(pGameManager->getGTexture(gID));
    
    ccTexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    m_groundSprite->getTexture()->setTexParameters(&texParams);
    
    this->addChild(m_groundSprite, 2);
	m_groundSprite->setAnchorPoint(ccp(0.0f, 1.0f));
	m_groundSprite->setColor(ccc3(0, 102, 255));
	ccBlendFunc gBlendFunc = { GL_ONE, GL_ZERO };
	m_groundSprite->setBlendFunc(gBlendFunc);
	m_groundSprite->setTextureRect(CCRectMake(0, 0, winSize.width, m_groundSprite->getContentSize().height));
    m_groundSprite->setPosition(ccp(0.0f, 90.0f));


	m_line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
	this->addChild(m_line, 3);
	m_line->setPosition(ccp(winSize.width * 0.5f, 90.5f));
	m_line->setAnchorPoint(ccp(0.5f, 1.0f));
	// m_line->setBlendFunc(0x302, 1);
	m_line->setTag(1);
	// m_line->setColor(ccc3(255, 255, 255));
    
    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, 90.0f));
    this->addChild(leftShadow, 3);
    leftShadow->setOpacity(100);
    leftShadow->setColor(ccc3(150, 150, 150));
    leftShadow->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
    leftShadow->setTag(0);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, 90.0f));
    rightShadow->setFlipX(true);
    this->addChild(rightShadow, 3);
    rightShadow->setOpacity(100);
    rightShadow->setColor(ccc3(150, 150, 150));
    rightShadow->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
    rightShadow->setTag(0);
    
    m_line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    this->addChild(m_line, 3);
    m_line->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 90.0f));
    
    m_isActive = false;
    
    return true;
}

void GJGroundLayer::fadeInGround(float duration)
{

}

void GJGroundLayer::fadeInFinished()
{
	this->m_isActive = true;
}

void GJGroundLayer::fadeOutGround(float duration)
{

}


void GJGroundLayer::draw()
{

}

void GJGroundLayer::deactivateGround()
{
	this->stopAllActions();
	CCArray* children = getChildren();
	for (int i = 0, count = children->count(); i < count; ++i) {
		((CCNode*)children->objectAtIndex(i))->stopActionByTag(999);
	}
	m_isActive = false;
}