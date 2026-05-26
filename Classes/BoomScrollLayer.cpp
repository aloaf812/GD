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
	m_dotsArray = nullptr;
	m_looped = false;
	unk_0x120 = nullptr;
	unk_0x124 = false;
	unk_0x134 = nullptr;
	m_internalLayer = nullptr;
	m_minTouchSpeed = 0.0f;
	m_touchSpeedFast = 0.0f;
	m_touchSpeedMid = 0.0f;
	m_delegate = nullptr;
	m_movingToPage = false;
	m_minimumTouchLengthToSlide = 0.0f;
	m_minimumTouchLengthToChangePage = 0.0f;
	m_marginOffset = 0.0f;
	m_stealTouches = false;
	m_showPagesIndicator = false;
	m_currentScreen = 0;
	m_pagesWidthOffset = 0.0f;
	m_pages = 0;
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

bool BoomScrollLayer::init(cocos2d::CCArray* pages, int offset, bool looped)
{
    if (!CCLayer::init())
        return false;
    
	m_internalLayer = ExtendedLayer::create();
	this->addChild(m_internalLayer);

	setObjType(CCObjectType::BoomScrollLayer);
    setTouchEnabled(true);
	setStealTouches(true);
	setMinimumTouchLengthToSlide(40.0f);
	setMinimumTouchLengthToChangePage(100.0f);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	setMarginOffset(winSize.width);
	setShowPagesIndicator(true);
	setPagesIndicatorPosition(ccp(getContentSize().width * 0.5f, 60.0f));
	setPagesIndicatorNormalColor(ccc4(150, 150, 150, 255));
	setPagesIndicatorSelectedColor(ccc4(255, 255, 255, 255));
	setScrollArea(CCRectMake(0.0f, 0.0f, winSize.width, winSize.height));

	// variables
	unk_0x134 = pages;
	m_currentScreen = 0;
	m_pagesWidthOffset = offset;
	m_minTouchSpeed = 0.3f;
	m_touchSpeedMid = 0.4f;
	m_touchSpeedFast = 0.6f;

	pages->retain();
	CCSpriteBatchNode* dots = CCSpriteBatchNode::create("smallDot.png", 29);
    this->addChild(dots, 5);
    m_dotsArray = CCArray::create();
	m_dotsArray->retain();
    
    for (int i = 0; i < getTotalPages(); ++i)
	{
        CCSprite* dot = CCSprite::create("smallDot.png");
        dots->addChild(dot);
		m_dotsArray->addObject(dot);
    }
    
    this->updatePages();

	this->m_looped = looped;
	if (looped)
		repositionPagesLooped();

	this->schedule(schedule_selector(BoomScrollLayer::updateDots), 0.1f);
    
	return true;
}

void BoomScrollLayer::updateDots(float dt)
{
	if (m_dotsArray != nullptr) {
		// add the missing logic lol
	}
}

void BoomScrollLayer::updatePages()
{
	for (unsigned int i = 0; i < unk_0x134->count(); ++i) {
		CCNode* page = (CCNode*)unk_0x134->objectAtIndex(i);
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
		moveToPageEnded();
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
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(BoomScrollLayer::moveToPageEnded));
		CCSequence* sequence = CCSequence::create(elasticMove, callback, nullptr);
		m_internalLayer->runAction(sequence);
		sequence->setTag(2);

		m_currentScreen = page;

		// if (m_looped != false)
			//repositionPagesLooped();

	}
}

void BoomScrollLayer::moveToPageEnded()
{
	// stuff
	m_internalLayer->stopActionByTag(2);
	// more stuff
	this->updateDots(0.0f);
}

// https://github.com/geode-sdk/bindings/blob/main/bindings/2.208/inline/BoomScrollLayer.cpp#L21
CCPoint BoomScrollLayer::positionForPageWithNumber(int page)
{
	return ccp(this->getContentSize().width * page, 0.f);
}

void BoomScrollLayer::repositionPagesLooped()
{
	// todo
}

void BoomScrollLayer::setPagesIndicatorPosition(CCPoint position)
{
	m_pagesIndicatorPosition = position;
	updateDots(0.0f);
}

int BoomScrollLayer::getTotalPages()
{
	CCArray* pagesArray;
	if (!unk_0x124)
		pagesArray = unk_0x134;
	else
		pagesArray = unk_0x120;

	return pagesArray->count();
}