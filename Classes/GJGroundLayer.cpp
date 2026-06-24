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
	m_line->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
	m_line->setTag(1);
	m_line->setColor(ccWHITE);
    
    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, 90.0f));
    this->addChild(leftShadow, 3);
    leftShadow->setTag(0);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, 90.0f));
    this->addChild(rightShadow, 3);
    rightShadow->setFlipX(true);
	rightShadow->setTag(0);

    leftShadow->setOpacity(100);
    rightShadow->setOpacity(100);
	
	leftShadow->setScaleX(0.7f);
	rightShadow->setScaleX(0.7f);

	ccBlendFunc sBlendFunc = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	leftShadow->setBlendFunc(sBlendFunc);
	rightShadow->setBlendFunc(sBlendFunc);
    
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

void GJGroundLayer::showGround()
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

// GJFlyGroundLayer
GJFlyGroundLayer* GJFlyGroundLayer::create()
{
	GJFlyGroundLayer *pRet = new GJFlyGroundLayer();
	if (pRet && pRet->init())
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


bool GJFlyGroundLayer::init()
{
	if (!CCLayer::init())
		return false;

	// unk_0x118 = 0;
	return true;
}