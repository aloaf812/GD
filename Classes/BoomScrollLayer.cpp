#include "BoomScrollLayer.h"
USING_NS_CC;

// BoomScrollLayerDelegate because being in a single file is cleaner

void BoomScrollLayerDelegate::scrollLayerMoved(cocos2d::CCPoint p0)
{

}

void BoomScrollLayerDelegate::scrollLayerScrolledToPage(BoomScrollLayer* bsl, int p1)
{

}

void BoomScrollLayerDelegate::scrollLayerScrollingStarted(BoomScrollLayer* bsl)
{
    
}

// now for the real BoomScrollLayer code
BoomScrollLayer::BoomScrollLayer()
{
    this->m_bslDelegate = nullptr;
    m_extendedLayer = nullptr;
    m_pageDots = nullptr;
    m_currentScreen = 0;
}

BoomScrollLayer* BoomScrollLayer::create(cocos2d::CCArray* pages, int param1, bool param2)
{
    BoomScrollLayer* ret = new BoomScrollLayer();
    if (ret) {
        if (ret->init(pages, param1, param2)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
    }

    return NULL;
}

bool BoomScrollLayer::init(cocos2d::CCArray* pages, int param1, bool param2)
{
    if (!CCLayer::init())
        return false;
    
    //CCDirector* pDirector = CCDirector::sharedDirector();
    
    m_extendedLayer = ExtendedLayer::create();
    this->addChild(m_extendedLayer);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchPriority(1);
     
     
    // robtop: this->setTouchSwallowEnabled(true);
    
    
    m_pages = pages;
    
    CCSpriteBatchNode* dots = CCSpriteBatchNode::create("smallDot.png");
    m_pageDots = CCArray::create();
    m_pageDots->retain();
    this->addChild(dots, 5);
    
    int totalPages = 13;
    for (int i = 0; i < totalPages; ++i)
    {
        CCSprite* dot = CCSprite::create("smallDot.png");
        dots->addChild(dot);
        m_pageDots->addObject(dot);
    }
    
    this->updatePages();
    
    this->schedule(schedule_selector(BoomScrollLayer::updateDots));
    
	return true;
}

void BoomScrollLayer::updateDots(float dt)
{
    //if (!m_pageDots) return;
}

void BoomScrollLayer::updatePages()
{
    if (!m_pages) return;
    const unsigned int totalPages = m_pages->count();
    for (unsigned int i = 0; i < totalPages; ++i) {
        auto page = dynamic_cast<CCNode*>(m_pages->objectAtIndex(i));
        if (!page) continue;
        
        page->setPosition(CCPointZero);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        page->setContentSize(winSize);
        
        float pageWidth = this->getContentSize().width;
        float pageSpacing = 13.0f; //= getPageSpacing();
        float xPos = i * (pageWidth - pageSpacing);
        
        page->setPosition(CCPoint(xPos, 0.0f));
        if (!page->getParent()) {
            m_extendedLayer->addChild(page);
        }
    }
}

bool BoomScrollLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocation();
    
    CCLOG("x: %f, y: %f", touchLocation.x, touchLocation.y);
    
    return true;
}

int BoomScrollLayer::getCurrentScreen()
{
    return m_currentScreen;
}

void BoomScrollLayer::quickUpdate()
{
    
}

void BoomScrollLayer::moveToPage(int page)
{
    float pos = (-555.0f * page);
    this->setPosition({pos, 0});
    CCLOG("moved to page %i", page);
    m_currentScreen = page;
}