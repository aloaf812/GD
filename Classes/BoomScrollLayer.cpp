#include "BoomScrollLayer.h"
#include "ExtendedLayer.h"
USING_NS_CC;

BoomScrollLayer::BoomScrollLayer()
{
	m_dotsArray = nullptr;
	m_animatingToPage = 0;
	unk_0x114 = 0.0f;
	unk_0x118 = 0.0f;
	m_looped = false;
	unk_0x120 = nullptr;
	unk_0x124 = false;
	unk_0x128 = 0;
	unk_0x12c = false;
	unk_0x130 = nullptr;
	m_actualPages = nullptr;
	unk_0x138 = 0.0f;
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

BoomScrollLayer* BoomScrollLayer::create(cocos2d::CCArray* pages, int offset, bool looped)
{
	BoomScrollLayer* ret = new BoomScrollLayer();
	if (ret) {
		if (ret->init(pages, offset, looped)) {
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

	setMarginOffset(WIN_SIZE.width);
	setShowPagesIndicator(true);
	setPagesIndicatorPosition(ccp(getContentSize().width * 0.5f, 60.0f));
	setPagesIndicatorNormalColor(ccc4(150, 150, 150, 255));
	setPagesIndicatorSelectedColor(ccc4(255, 255, 255, 255));
	setScrollArea(CCRectMake(0.0f, 0.0f, WIN_SIZE.width, WIN_SIZE.height));

	m_actualPages = pages;
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

	for (int i = 0; i < getTotalPages(); ++i) {
		CCSprite* dot = CCSprite::create("smallDot.png");
		dots->addChild(dot);
		m_dotsArray->addObject(dot);
	}

	this->updatePages();

	m_looped = looped;
	if (looped)
		repositionPagesLooped();

	this->schedule(schedule_selector(BoomScrollLayer::updateDots), 0.1f);

	return true;
}

void BoomScrollLayer::updateDots(float dt)
{
	// guard was inverted in original,
	// should be if (m_dotsArray), not if (!m_dotsArray)
	if (m_dotsArray) {
		int pageNum = pageNumberForPosition(m_internalLayer->getPosition());

		if (m_looped)
			pageNum = getRelativePageForNum(pageNum);

		for (int i = 0; i < getTotalPages(); ++i) {
			if (i < (int)m_dotsArray->count()) {
				CCSprite* dot = (CCSprite*)m_dotsArray->objectAtIndex(i);
				dot->setColor(i == pageNum ? ccWHITE : ccGRAY);

				// position each dot around m_pagesIndicatorPosition
				dot->setPosition(ccp(
					m_pagesIndicatorPosition.x + (i - getTotalPages() * 0.5f + 0.5f) * 14.0f,
					m_pagesIndicatorPosition.y));
			}
		}
	}
}

void BoomScrollLayer::updatePages()
{
	for (int i = 0; i < (int)m_actualPages->count(); ++i) {
		CCNode* page = (CCNode*)m_actualPages->objectAtIndex(i);
		page->setAnchorPoint(ccp(0.0f, 0.0f));
		page->setContentSize(WIN_SIZE);
		// FIX: pages should be positioned by index, not all at same X
		page->setPosition(ccp(
			(getContentSize().width + m_pagesWidthOffset) * i,
			0.0f));

		if (!page->getParent())
			m_internalLayer->addChild(page);
	}
}

bool BoomScrollLayer::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	return true;
}

void BoomScrollLayer::quickUpdate()
{
	if (m_movingToPage) {
		m_movingToPage = false;
		m_internalLayer->stopActionByTag(2);
		m_internalLayer->setPosition(m_targetPos);
		moveToPageEnded();
	}
}

void BoomScrollLayer::moveToPage(int page)
{
	if (m_looped || (-1 < page && page < getTotalPages())) {
		m_movingToPage = true;
		m_targetPos = positionForPageWithNumber(page);
		m_internalLayer->stopActionByTag(2);

		float speed;
		if (unk_0x118 > m_touchSpeedFast)
			speed = 0.4f;
		else if (unk_0x118 > m_touchSpeedMid)
			speed = 0.6f;
		else
			speed = 0.8f;

		unk_0x118 = 0.0f;

		CCMoveTo* moveAction = CCMoveTo::create(speed * 1.2f, m_targetPos);
		CCEaseElasticOut* elasticMove = CCEaseElasticOut::create(moveAction, 0.5f);
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(BoomScrollLayer::moveToPageEnded));
		CCSequence* sequence = CCSequence::create(elasticMove, callback, nullptr);
		sequence->setTag(2);
		m_internalLayer->runAction(sequence);

		// update screen index immediately so onPrev/onNext reads correct value
		m_currentScreen = page;

		if (m_looped)
			repositionPagesLooped();

		if (m_delegate)
			m_delegate->scrollLayerMoved(m_targetPos);
	}
}

void BoomScrollLayer::instantMoveToPage(int page)
{
	if (m_looped || (-1 < page && page < getTotalPages())) {
		m_internalLayer->stopActionByTag(2);
		m_movingToPage = false;
		CCPoint pos = positionForPageWithNumber(page);
		m_internalLayer->setPosition(pos);
		m_currentScreen = page;

		if (m_looped)
			repositionPagesLooped();

		if (m_delegate)
			m_delegate->scrollLayerMoved(pos);

		moveToPageEnded();
	}
}

void BoomScrollLayer::moveToPageEnded()
{
	if ((m_animatingToPage != m_currentScreen) && m_delegate) {
		m_delegate->scrollLayerScrollingStarted(this);
	}

	m_internalLayer->stopActionByTag(2);

	// FIX: use our corrected pageNumberForPosition
	int pageNum = pageNumberForPosition(m_internalLayer->getPosition());
	m_currentScreen = pageNum;
	m_animatingToPage = pageNum;

	if (m_delegate)
		m_delegate->scrollLayerScrolledToPage(this, pageNum);

	updateDots(0.0f);
}

// this part really hurts my head
// pages go left as index increases, so internalLayer moves in negative X.
// positionForPageWithNumber and pageNumberForPosition must be inverses.
CCPoint BoomScrollLayer::positionForPageWithNumber(int page)
{
	// FIX: negative X so pages scroll left correctly
	return ccp(-((getContentSize().width + m_pagesWidthOffset) * (float)page), 0.0f);
}

CCPoint BoomScrollLayer::getRelativePosForPage(int page)
{
	return ccp((getContentSize().width - m_pagesWidthOffset) * (float)page, 0.0f);
}

void BoomScrollLayer::repositionPagesLooped()
{
	int page1 = getRelativePageForNum(m_currentScreen);
	int page2 = getRelativePageForNum(m_currentScreen - 1);
	int page3 = getRelativePageForNum(m_currentScreen + 1);

	int actualPage2 = page2;
	int actualPage3 = page3;

	if (unk_0x124) {
		getPage(m_currentScreen)->setPosition(getRelativePosForPage(m_currentScreen));
		actualPage2 = m_currentScreen - 1;
		actualPage3 = m_currentScreen + 1;
	}

	getPage(actualPage2)->setPosition(getRelativePosForPage(actualPage2));
	getPage(actualPage3)->setPosition(getRelativePosForPage(actualPage3));

	for (int i = 0; i < (int)m_actualPages->count(); ++i)
		((CCLayer*)m_actualPages->objectAtIndex(i))->setVisible(false);

	getPage(page1)->setVisible(true);
	getPage(actualPage2)->setVisible(true);
	getPage(actualPage3)->setVisible(true);
}

void BoomScrollLayer::setPagesIndicatorPosition(CCPoint position)
{
	m_pagesIndicatorPosition = position;
	updateDots(0.0f);
}

int BoomScrollLayer::getTotalPages()
{
	CCArray* pagesArray = unk_0x124 ? unk_0x120 : m_actualPages;
	return (int)pagesArray->count();
}

// FIX: proper inverse of positionForPageWithNumber
// pos.x is negative, so negate it before dividing
int BoomScrollLayer::pageNumberForPosition(CCPoint pos)
{
	float pageWidth = getContentSize().width + m_pagesWidthOffset;
	if (pageWidth == 0.0f)
		return 0;

	int page = (int)roundf(-pos.x / pageWidth);

	int total = getTotalPages();
	if (page < 0)      page = 0;
	if (page >= total) page = total - 1;

	return page;
}

int BoomScrollLayer::getRelativePageForNum(int page)
{
	int pages = getTotalPages();
	if (page > 0) return page % pages;
	while (page < 0) page += pages;
	return page;
}

CCLayer* BoomScrollLayer::getPage(int page)
{
	if (unk_0x124) {
		int totalPgs = (int)m_actualPages->count();
		if (page < 0)
			for (; page < 0; page += totalPgs) {}
		else
			page %= totalPgs;
	}
	return (CCLayer*)m_actualPages->objectAtIndex(page);
}

void BoomScrollLayer::addPage(CCLayer* aPage)
{
	addPage(aPage, (int)m_actualPages->count());
}

void BoomScrollLayer::addPage(CCLayer* aPage, int pageNumber)
{
	pageNumber = MIN(pageNumber, (int)m_actualPages->count());
	pageNumber = MAX(pageNumber, 0);

	m_actualPages->insertObject(aPage, pageNumber);

	updatePages();
	moveToPage(m_currentScreen);
}