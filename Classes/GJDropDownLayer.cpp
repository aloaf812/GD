// Decompiled by WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/GJDropDownLayer.cpp
#include "GJDropDownLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
USING_NS_CC;
GJDropDownLayer::GJDropDownLayer() {
    m_endPosition = ccp(0, 0);
    m_startPosition = ccp(0, 0);
	m_uiMenu = NULL;
    m_listLayer = NULL;
    m_internalLayer = NULL;
    m_hidden = false;
    m_delegate = NULL;
}

void GJDropDownLayer::disableUI() {
    m_uiMenu->setTouchEnabled(false);
}

void GJDropDownLayer::enableUI() {
	m_uiMenu->setTouchEnabled(true);
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
	CCDirector::sharedDirector()->getTouchDispatcher()->setForcePrio(false);
    this->disableUI();
    this->hideLayer(false);
}

void GJDropDownLayer::hideLayer(bool instantHide) { 
    m_internalLayer->stopAllActions();
    
    if (instantHide) {
		m_internalLayer->setPosition(m_startPosition);
        this->setOpacity(0);
        this->layerHidden();
    }
    else {
        CCEaseInOut* action = CCEaseInOut::create(CCMoveTo::create(0.5, m_startPosition), 2.0f);
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::layerHidden));
		m_internalLayer->runAction(CCSequence::create(action, callback, NULL));
        this->runAction(CCFadeTo::create(0.5, 0));
    }
}

void GJDropDownLayer::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2147483651, true);
}

void GJDropDownLayer::keyBackClicked() {
    this->exitLayer(NULL);
}

void GJDropDownLayer::layerHidden() {
    this->setVisible(false);

	if (m_removeOnExit)
        this->removeFromParentAndCleanup(true);
}

void GJDropDownLayer::layerVisible() {
    this->setVisible(true);
}

void GJDropDownLayer::showLayer(bool instantShow) {
    m_internalLayer->stopAllActions();
    this->layerVisible();
    
    if (instantShow) {
        m_internalLayer->setPosition(m_endPosition);
        this->setOpacity(125);
        this->enterAnimFinished();
		return;
	}
	
    CCEaseInOut* action = CCEaseInOut::create(CCMoveTo::create(0.5f, m_endPosition), 2.0f);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::enterAnimFinished));
    m_internalLayer->runAction(CCSequence::create(action, callback, nullptr));
    this->setOpacity(0);
    this->runAction(CCFadeTo::create(0.5f, 125));
}

bool GJDropDownLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
	return true;
}

void GJDropDownLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {}
void GJDropDownLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent) {}
void GJDropDownLayer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {}

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
	CCDirector::sharedDirector()->getTouchDispatcher()->setForcePrio(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->setTargetPrio(2147483650);

	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)))
        return false;
    
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_internalLayer = CCLayer::create();
    this->addChild(m_internalLayer);
    
    m_endPosition = ccp(0, 0);
    m_startPosition = ccp(0, winSize.height);
    
    m_internalLayer->setPosition(m_startPosition);
	m_listLayer = GJListLayer::create(NULL, title, ccc4(0, 0, 0, 180), 356.0, height);
    m_internalLayer->addChild(m_listLayer);
    
    m_listLayer->setPosition(ccp((winSize.width - 356.0f) * 0.5f, (((winSize.height - height) * 0.5f) - 10.0f) + 5.0f));

    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(GJDropDownLayer::exitLayer));
    backBtn->setSizeMult(2.0f);
    
	m_uiMenu = CCMenu::create(backBtn, NULL);
	m_uiMenu->setPosition(ccp((winSize.width * 0.5f) + 178.0f, (winSize.height * 0.5f) - (height * 0.5f)));
    
	m_uiMenu->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() + 24, CCDirector::sharedDirector()->getScreenTop() - 23));
    
	m_internalLayer->addChild(m_uiMenu, 10);
    
	float height2 = height + m_listLayer->getPosition().y + 12.0;
    CCSprite* chain1 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    m_internalLayer->addChild(chain1, -1);
	chain1->setAnchorPoint(ccp(0.5, 0.0));
	chain1->setPosition(ccp((winSize.width * 0.5f) - 156.0f, height2));
    chain1->setTag(0);
    
    CCSprite* chain2 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    m_internalLayer->addChild(chain2, -1);
	chain2->setAnchorPoint(ccp(0.5, 0.0));
	chain2->setPosition(ccp((winSize.width * 0.5f) + 156.0f, height2));
    chain2->setTag(1);
    
	m_removeOnExit = false;
    this->hideLayer(true);
	m_removeOnExit = true;
    
    this->customSetup();
    
    return true;
}

void GJDropDownLayerDelegate::dropDownLayerWillClose(GJDropDownLayer *p0)
{
    
}