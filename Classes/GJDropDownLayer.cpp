// Decompiled by WylieMaster: https://github.com/Wyliemaster/GD-Decompiled/blob/main/GD/code/src/GJDropDownLayer.cpp
#include "GJDropDownLayer.h"
#include "CCMenuItemSpriteExtra.h"
USING_NS_CC;
GJDropDownLayer::GJDropDownLayer() {
    this->m_endPosition = ccp(0, 0);
    this->m_startPosition = ccp(0, 0);
    this->m_buttonMenu = NULL;
    this->m_listLayer = NULL;
    this->m_controllerEnabled = false;
    this->m_mainLayer = NULL;
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
        this->draw();
}

void GJDropDownLayer::enterLayer() {
    this->enableUI();
    this->showLayer(false);
}

void GJDropDownLayer::exitLayer(CCObject* p) {
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
    
    this->m_mainLayer->stopAllActions();
    
    if (instantHide) {
        this->m_mainLayer->setPosition(this->m_startPosition);
        this->setOpacity(0);
        this->layerHidden();
    }
    else {
        auto action = CCEaseInOut::create(CCMoveTo::create(0.5, this->m_startPosition), 2.);
        auto callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::exitLayer));
        auto seq = CCSequence::create(action, callback);
        this->m_mainLayer->runAction(seq);
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
    if (this->m_hidden)
        this->removeFromParentAndCleanup(true);
}

void GJDropDownLayer::layerVisible() {
    this->setVisible(true);
}

void GJDropDownLayer::showLayer(bool instantShow) {
    this->m_mainLayer->stopAllActions();
    this->layerVisible();
    
    if (instantShow) {
        this->m_mainLayer->setPosition(this->m_endPosition);
        this->setOpacity(125);
        this->enterAnimFinished();
    }
    else {
        auto action = CCEaseInOut::create(CCMoveTo::create(0.5, this->m_endPosition), 2.);
        auto callback = CCCallFunc::create(this, callfunc_selector(GJDropDownLayer::enterLayer));
        this->m_mainLayer->runAction(CCSequence::create(action, callback));
        this->setOpacity(0);
        this->runAction(CCFadeTo::create(0.5, 125));
    }
}

GJDropDownLayer* GJDropDownLayer::create(const char* title, float height) {
    auto pRet = new GJDropDownLayer();
    
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
    // what's this?: CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
    
    // i'm not sure why almost all gd decomps don't create struct variables which is the correct way to use ccColor stuff
    ccColor4B initColor = { 0, 0, 0, 125 };
    if (!this->initWithColor(initColor))
        return false;
    
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    // don't need this yet: this->setKeyboardEnabled(true);
    
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    this->m_mainLayer = CCLayer::create();
    this->addChild(this->m_mainLayer);
    
    this->m_endPosition = ccp(0, 0);
    this->m_startPosition = ccp(0, winSize.height);
    
    this->m_mainLayer->setPosition(this->m_startPosition);
    ccColor4B listColor = { 0, 0, 0, 180 };
    this->m_listLayer = GJListLayer::create(NULL, title, listColor, 356.0, height); // it shows -76 in decomp but 0xB4 in asm so i guess its 0xB4 :P
    this->m_mainLayer->addChild(this->m_listLayer);
    
    // this->m_listLayer->setPosition({ (winSize.width - 356.0) * 0.5, (((winSize.height - height) * 0.5) - 10.0) + 5.0 });
    // fixed this
    this->m_listLayer->setPosition(CCPoint((winSize.width - 356.0f) * 0.5f, (((winSize.height - height) * 0.5f) - 10.0f) + 5.0f));

    auto spr = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    auto btn = CCMenuItemSpriteExtra::create(spr, NULL, this, menu_selector(GJDropDownLayer::exitLayer)); // not sure about GJDropDownLayer::exitLayer, again &stru_274.st_value
    btn->setSizeMult(1.6);
    
    this->m_buttonMenu = CCMenu::create(btn);
    // this->m_buttonMenu->setPosition(CCPoint((winSize.width * 0.5) + 178.0, (winSize.height * 0.5) - (height * 0.5));
    // also fixed
    this->m_buttonMenu->setPosition(CCPoint((winSize.width * 0.5f) + 178.0f, (winSize.height * 0.5f) - (height * 0.5f)));
    
    // todo: make sense
    
    auto director = CCDirector::sharedDirector();
    // this->m_buttonMenu->setPosition({ director->getScreenLeft() + 24, director->getScreenTop() - 23 });
    this->m_buttonMenu->setPosition(CCPoint(director->getScreenLeft() + 24, director->getScreenTop() - 23));
    
    this->m_mainLayer->addChild(this->m_buttonMenu, 10);
    
    auto chain1 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    this->m_mainLayer->addChild(chain1, -1);
    // please fix your structs
    chain1->setAnchorPoint(CCPoint(0.5, 0.0 ));
    // chain1->setPosition({ (winSize.width * 0.5) - 156.0, height + this->m_listLayer->getPosition().y + 12.0 });
    chain1->setPosition(CCPoint((winSize.width * 0.5f) - 156.0f, height + this->m_listLayer->getPosition().y + 12.0));
    chain1->setTag(0);
    
    auto chain2 = CCSprite::createWithSpriteFrameName("chain_01_001.png");
    this->m_mainLayer->addChild(chain2, -1);
    chain2->setAnchorPoint(CCPoint(0.5, 0.0));
    // chain2->setPosition({ (winSize.width * 0.5) + 156.0, height + this->m_listLayer->getPosition().y + 12.0 });
    chain2->setPosition(CCPoint((winSize.width * 0.5f) + 156.0f, height + this->m_listLayer->getPosition().y + 12.0));
    chain2->setTag(1);
    
    this->m_hidden = false;
    this->hideLayer(true);
    this->m_hidden = true;
    
    this->customSetup();
    
    // 1.7 had no controller support :)
    // this just makes my life easier because it's less java/obj-c code to decompile
    /*if (PlatformToolbox::isControllerConnected() && !this->m_controllerEnabled)
        GameToolbox::addBackButton(this->m_mainLayer, btn);*/
    
    return true;
}

void GJDropDownLayerDelegate::dropDownLayerWillClose(GJDropDownLayer *p0)
{
    
}