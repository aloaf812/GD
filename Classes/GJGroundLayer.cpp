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
    m_tiles = nullptr;
    m_repeatCount = 0;
}

GJGroundLayer* GJGroundLayer::create(int gID)
{
    GJGroundLayer* ret = new GJGroundLayer();
    if (ret) {
        if (ret->init(gID)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
    }

    return NULL;
}

bool GJGroundLayer::init(int gID)
{
	if (!CCLayer::init())
    	return false;

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    GameManager* pGameManager = GameManager::sharedState();

   	m_groundSprite = CCSprite::create(pGameManager->getGTexture(gID));
    
    ccTexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    m_groundSprite->getTexture()->setTexParameters(&texParams);
    
    this->addChild(m_groundSprite, 2);
    m_groundSprite->setAnchorPoint({0, 1});
   	m_groundSprite->setColor({ 0, 102, 255 });
    m_groundSprite->setPosition({0.0f, 90.0f});
    
    float groundWidth = m_groundSprite->getTextureRect().size.width;
    float scaleFactor = getScaleX();
    m_groundWidth = groundWidth * scaleFactor;
    
    m_repeatCount = std::ceil(winSize.width / m_groundWidth) + 1.0f;
    m_repeatWidth = m_groundWidth * m_repeatCount;
    
    m_tiles = CCArray::create();
    m_tiles->retain();
    
    for (int i = 1; i < m_repeatCount; ++i) {
        CCSprite* tile = CCSprite::create(pGameManager->getGTexture(gID));
        tile->setAnchorPoint({0, 1});
        tile->setColor(ccc3(0, 102, 255));
        tile->setPosition(ccp(m_groundWidth * i, 90.0f));
        this->addChild(tile);
        m_tiles->addObject(tile);
    }
    
    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    leftShadow->setPosition(ccp(pDirector->getScreenLeft() - 1.0f, 90.0f));
    this->addChild(leftShadow, 3);
    leftShadow->setOpacity(100);
    leftShadow->setColor({150, 150, 150});
    leftShadow->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
    leftShadow->setTag(0);
    
    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    rightShadow->setPosition(ccp(pDirector->getScreenRight() + 1.0f, 90.0f));
    rightShadow->setFlipX(true);
    this->addChild(rightShadow, 3);
    rightShadow->setOpacity(100);
    rightShadow->setColor({150, 150, 150});
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
		dynamic_cast<CCNode*>(children->objectAtIndex(i))->stopActionByTag(999);
	}
	m_isActive = false;
}