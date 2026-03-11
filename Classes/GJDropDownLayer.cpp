// Decompiled by WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/GJDropDownLayer.cpp
#include "GJDropDownLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
USING_NS_CC;
GJDropDownLayer::GJDropDownLayer() {
    this->m_endPosition = ccp(0, 0);
    this->m_startPosition = ccp(0, 0);
    this->m_buttonMenu = NULL;
    this->m_listLayer = NULL;
    this->m_controllerEnabled = false;
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
    
    // auto director = CCDirector::sharedDirector();
    // director->getTouchDispatcher()->m_bForcePrio = false;
    
    this->disableUI();
    this->hideLayer(false);
}

void GJDropDownLayer::hideLayer(bool instantHide) {
    if (this->m_hidden) {
        if (this->m_delegate)
            this->m_delegate->dropDownLayerWillClose(this);
    }
    
    this->m_internalLayer->stopAllActions();
    
    if (instantHide) {
        this->m_internalLayer->setPosition(this->m_startPosition);
        this->setOpacity(0);
        this->layerHidden();
    }
    else {
        /*CCEaseInOut* action = CCEaseInOut::create(CCMoveTo::create(0.5, this->m_startPosition), 2.0f);
        CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::exitLayer));
		m_internalLayer->runAction(CCSequence::create(action, callback));
        this->runAction(CCFadeTo::create(0.5, 0));*/
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
    if (this->m_hidden)
        this->removeFromParentAndCleanup(true);
}

void GJDropDownLayer::layerVisible() {
    this->setVisible(true);
}

void GJDropDownLayer::showLayer(bool instantShow) {
    this->m_internalLayer->stopAllActions();
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
	touchDisp->setTargetPrio(-504); // i really dont know if this number is right lol

	if (!this->initWithColor(ccc4(0, 0, 0, 125)))
        return false;
    
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    // don't need this yet: this->setKeyboardEnabled(true);
    
	CCSize winSize = pDirector->getWinSize();
    
    this->m_internalLayer = CCLayer::create();
    this->addChild(this->m_internalLayer);
    
    this->m_endPosition = ccp(0, 0);
    this->m_startPosition = ccp(0, winSize.height);
    
    m_internalLayer->setPosition(this->m_startPosition);
    ccColor4B listColor = { 0, 0, 0, 180 };
    this->m_listLayer = GJListLayer::create(NULL, title, listColor, 356.0, height); // it shows -76 in decomp but 0xB4 in asm so i guess its 0xB4 :P
    m_internalLayer->addChild(this->m_listLayer);
    
    this->m_listLayer->setPosition(CCPoint((winSize.width - 356.0f) * 0.5f, (((winSize.height - height) * 0.5f) - 10.0f) + 5.0f));

    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, NULL, this, menu_selector(GJDropDownLayer::exitLayer));
    backBtn->setSizeMult(1.6f);
    
    this->m_buttonMenu = CCMenu::create(backBtn, NULL);
    // this->m_buttonMenu->setPosition(CCPoint((winSize.width * 0.5) + 178.0, (winSize.height * 0.5) - (height * 0.5));
    // also fixed
    this->m_buttonMenu->setPosition(CCPoint((winSize.width * 0.5f) + 178.0f, (winSize.height * 0.5f) - (height * 0.5f)));
    
    // todo: make sense
    
    // this->m_buttonMenu->setPosition({ director->getScreenLeft() + 24, director->getScreenTop() - 23 });
	this->m_buttonMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 24, pDirector->getScreenTop() - 23));
    
    this->m_internalLayer->addChild(this->m_buttonMenu, 10);
    
    CCSprite* chain1 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    this->m_internalLayer->addChild(chain1, -1);
    // please fix your structs
    chain1->setAnchorPoint(CCPoint(0.5, 0.0));
    // chain1->setPosition({ (winSize.width * 0.5) - 156.0, height + this->m_listLayer->getPosition().y + 12.0 });
    chain1->setPosition(CCPoint((winSize.width * 0.5f) - 156.0f, height + this->m_listLayer->getPosition().y + 12.0));
    chain1->setTag(0);
    
    CCSprite* chain2 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    this->m_internalLayer->addChild(chain2, -1);
    chain2->setAnchorPoint(CCPoint(0.5, 0.0));
    // chain2->setPosition({ (winSize.width * 0.5) + 156.0, height + this->m_listLayer->getPosition().y + 12.0 });
    chain2->setPosition(CCPoint((winSize.width * 0.5f) + 156.0f, height + this->m_listLayer->getPosition().y + 12.0));
    chain2->setTag(1);
    
    this->m_hidden = false;
    this->hideLayer(true);
    this->m_hidden = true;
    
    this->customSetup();
    
    return true;
}

void GJDropDownLayerDelegate::dropDownLayerWillClose(GJDropDownLayer *p0)
{
    
}