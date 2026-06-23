#include "GJDropDownLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

USING_NS_CC;

GJDropDownLayer::GJDropDownLayer() {
	this->m_endPosition = ccp(0, 0);
	this->m_startPosition = ccp(0, 0);
	this->m_buttonMenu = NULL;
	this->m_listLayer = NULL;
	this->m_internalLayer = NULL;
	this->m_hidden = false;
	this->m_delegate = NULL;
}

GJDropDownLayer::~GJDropDownLayer() {
	// CCDirector::sharedDirector()->getTouchDispatcher()->decrementForcePrio(2);
}

void GJDropDownLayer::disableUI() {
	this->m_buttonMenu->setTouchEnabled(false);
}

void GJDropDownLayer::enableUI() {
	this->m_buttonMenu->setTouchEnabled(true);
}

void GJDropDownLayer::draw() {
	if (this->getOpacity())
		CCLayerColor::draw();
}

void GJDropDownLayer::enterLayer() {
	this->enableUI();
	this->showLayer(false);
}

void GJDropDownLayer::exitLayer(CCObject* sender) {
	this->setKeypadEnabled(false);

	CCDirector* director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->setForcePrio(false);

	if (this->m_delegate) {
		this->m_delegate->dropDownLayerWillClose(this);
	}

	this->disableUI();
	this->hideLayer(false);
}

void GJDropDownLayer::hideLayer(bool instantHide) {
	this->m_internalLayer->stopAllActions();

	if (instantHide) {
		m_internalLayer->setPosition(m_startPosition);
		this->setOpacity(0);
		this->layerHidden();
	}
	else {
		CCEaseInOut* action = CCEaseInOut::create(CCMoveTo::create(0.5, this->m_startPosition), 2.0f);
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::layerHidden));
		m_internalLayer->runAction(CCSequence::create(action, callback, NULL));
		this->runAction(CCFadeTo::create(0.5, 0));
	}
}

void GJDropDownLayer::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, true);
}

void GJDropDownLayer::keyBackClicked() {
	this->exitLayer(NULL);
}

void GJDropDownLayer::layerHidden() {
	this->setVisible(false);

	if (this->m_removeOnExit) {
		this->removeFromParentAndCleanup(true);
	}
}

void GJDropDownLayer::layerVisible() {
	this->setVisible(true);
}

void GJDropDownLayer::showLayer(bool instantShow) {
	m_internalLayer->stopAllActions();
	this->layerVisible();

	if (instantShow) {
		this->m_internalLayer->setPosition(this->m_endPosition);
		this->setOpacity(125);
		this->enterAnimFinished();
		return;
	}

	CCEaseInOut* action = CCEaseInOut::create(CCMoveTo::create(0.5, this->m_endPosition), 2.0f);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::enterAnimFinished));
	m_internalLayer->runAction(CCSequence::create(action, callback, nullptr));
	this->setOpacity(0);
	this->runAction(CCFadeTo::create(0.5, 125));
}

bool GJDropDownLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
	return true;
}

GJDropDownLayer* GJDropDownLayer::create(const char* title, float height) {
	GJDropDownLayer* pRet = new GJDropDownLayer();

	if (pRet && pRet->init(title, height)) {
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

GJDropDownLayer* GJDropDownLayer::create(const char* title) {
	return GJDropDownLayer::create(title, 220);
}

bool GJDropDownLayer::init(const char* title) {
	return this->init(title, 220);
}

bool GJDropDownLayer::init(const char* title, float height) {
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCTouchDispatcher* touchDisp = pDirector->getTouchDispatcher();

	touchDisp->setForcePrio(true);
	touchDisp->setTargetPrio(-504);

	if (!this->initWithColor(ccc4(0, 0, 0, 125)))
		return false;

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	CCSize winSize = pDirector->getWinSize();

	this->m_internalLayer = CCLayer::create();
	this->addChild(this->m_internalLayer);

	this->m_endPosition = ccp(0, 0);
	this->m_startPosition = ccp(0, winSize.height);

	m_internalLayer->setPosition(this->m_startPosition);
	ccColor4B listColor = { 0, 0, 0, 180 };
	this->m_listLayer = GJListLayer::create(NULL, title, listColor, 356.0, height);
	m_internalLayer->addChild(this->m_listLayer);

	this->m_listLayer->setPosition(CCPoint((winSize.width - 356.0f) * 0.5f, (((winSize.height - height) * 0.5f) - 10.0f) + 5.0f));
	float height2 = height + m_listLayer->getPosition().y + 12.0;

	CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
	CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(GJDropDownLayer::exitLayer));
	backBtn->setSizeMult(1.6f);

	this->m_buttonMenu = CCMenu::create(backBtn, NULL);
	this->m_buttonMenu->setPosition(CCPoint((winSize.width * 0.5f) + 178.0f, (winSize.height * 0.5f) - (height * 0.5f)));
	this->m_buttonMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 24, pDirector->getScreenTop() - 23));

	m_internalLayer->addChild(m_buttonMenu, 10);

	CCSprite* chain1 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
	this->m_internalLayer->addChild(chain1, -1);
	chain1->setAnchorPoint(CCPoint(0.5, 0.0));
	chain1->setPosition(CCPoint((winSize.width * 0.5f) - 156.0f, height2));
	chain1->setTag(0);

	CCSprite* chain2 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
	this->m_internalLayer->addChild(chain2, -1);
	chain2->setAnchorPoint(CCPoint(0.5, 0.0));
	chain2->setPosition(CCPoint((winSize.width * 0.5f) + 156.0f, height2));
	chain2->setTag(1);

	m_removeOnExit = false;
	this->hideLayer(true);
	m_removeOnExit = true;

	this->customSetup();

	return true;
}

void GJDropDownLayerDelegate::dropDownLayerWillClose(GJDropDownLayer *p0) { }