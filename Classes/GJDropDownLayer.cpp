// Decompiled by WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/GJDropDownLayer.cpp
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

void GJDropDownLayer::disableUI() {
    m_buttonMenu->setTouchEnabled(false);
}

void GJDropDownLayer::enableUI() {
    m_buttonMenu->setTouchEnabled(true);
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
        m_internalLayer->setPosition(this->m_endPosition);
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

bool GJDropDownLayer::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
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
    
    m_buttonMenu = CCMenu::create(backBtn, NULL);
	m_buttonMenu->setPosition(ccp((winSize.width * 0.5f) + 178.0f, (winSize.height * 0.5f) - (height * 0.5f)));
    
	m_buttonMenu->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() + 24, CCDirector::sharedDirector()->getScreenTop() - 23));
    
    m_internalLayer->addChild(m_buttonMenu, 10);
    
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