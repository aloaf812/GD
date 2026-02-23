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

bool BoomScrollLayer::init(cocos2d::CCArray* pages, int param1, bool looped)
{
    if (!CCLayer::init())
        return false;
    
    //CCDirector* pDirector = CCDirector::sharedDirector();
    
	m_internalLayer = ExtendedLayer::create();
	this->addChild(m_internalLayer);

    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchPriority(1);
     
     
    // robtop: this->setTouchSwallowEnabled(true);
    
	this->m_minTouchSpeed = 0.3;
	this->m_currentScreen = 0;
	this->m_touchSpeedMid = 0.4;
	this->m_touchSpeedFast = 0.6;


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
	this->m_looped = looped;

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
			m_internalLayer->addChild(page);
        }
    }
}

bool BoomScrollLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocation();
    
    CCLOG("x: %f, y: %f", touchLocation.x, touchLocation.y);
    
    return true;
}

void BoomScrollLayer::quickUpdate()
{
	if (this->m_movingToPage != false) {
		this->m_movingToPage = false;
		m_internalLayer->stopActionByTag(2);
		m_internalLayer->setPosition(m_targetPos);
		//moveToPageEnded();
	}
}

void BoomScrollLayer::moveToPage(int page)
{
	if (m_looped != false) {
		m_movingToPage = true;
		m_targetPos = this->positionForPageWithNumber(page);
		m_internalLayer->stopActionByTag(2);

		CCMoveTo* moveAction = CCMoveTo::create((0.8f * 1.2f), m_targetPos);
		CCEaseElasticOut* elasticMove = CCEaseElasticOut::create(moveAction, 0.5f);
		// CCSequence* sequence = CCSequence::create({})
		m_internalLayer->runAction(elasticMove);

		m_currentScreen = page;

	}
    CCLOG("moved to page %i", page);
}

// https://github.com/geode-sdk/bindings/blob/main/bindings/2.208/inline/BoomScrollLayer.cpp#L21
CCPoint BoomScrollLayer::positionForPageWithNumber(int page)
{
	return { this->getContentSize().width * page, 0.f };
}