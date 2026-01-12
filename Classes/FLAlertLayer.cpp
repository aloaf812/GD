#include "FLAlertLayer.h"
#include "TextArea.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
USING_NS_CC;

/*FLAlertLayer::FLAlertLayer()
{
    m_buttonMenu = nullptr;
    m_ZOrder = 0;
    m_alertProtocol = nullptr;
    m_scene = nullptr;
    m_reverseKeyBack = false;
    m_mainLayer = nullptr;
    m_scrollAction = -1;
    m_containsBorder = false;
    m_noAction = false;
}

bool FLAlertLayer::init(FLAlertLayerProtocol* target, char const* title, std::string caption, char const* button1, char const* button2, float width, bool border, float height) {
    if (!cocos2d::CCLayerColor::initWithColor(ccc4(0,0,0,150))) return false;
    m_containsBorder = border;
    CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
    
    setTouchEnabled(true);
    setKeypadEnabled(true);
    setKeypadEnabled(true);
    m_reverseKeyBack = false;
    m_alertProtocol = target;
    
    auto windowSize = CCDirector::sharedDirector()->getWinSize();
    
    m_mainLayer = cocos2d::CCLayer::create();
    addChild(m_mainLayer);
    
    TextArea* textArea;
    if (!m_containsBorder) {
        textArea = TextArea::create(caption, "chatFont.fnt", 1.0, width - 60.0, CCPointMake(0.5, 0.5), 20.0, false);
        m_mainLayer->addChild(textArea, 3);
        height = textArea->m_obRect.size.height + 120;
        height = std::max(height, 140.0f);
    }
    // honestly this is there but not added anywhere what
    // auto layerColor = CCLayerColor::create(ccc4(0,0,0,255), width, height);
    // auto layerColorPos = CCPointMake(windowSize.width - width, windowSize.height - height) * 0.5;
    // layerColor->setPosition(layerColorPos);
    // layerColor->setVisible(false);
    
    // auto layerColor2 = CCLayerColor::create(ccc4(150,150,150,255), width + 16, height + 16);
    // auto layerColor2Pos = layerColorPos - CCPointMake(8, 8);
    // layerColor2->setPosition(layerColor2Pos);
    // layerColor2->setVisible(false);
    
    auto scale9 = extension::CCScale9Sprite::create("square01_001.png", CCRectMake(0, 0, 94, 94));
    scale9->setContentSize(CCSizeMake(width, height));
    auto scale9Pos = CCPointMake(windowSize.width*0.5, windowSize.height*0.5);
    scale9->setPosition(scale9Pos);
    m_mainLayer->addChild(scale9, 1);
    
    auto titleText = CCLabelBMFont::create(title, "goldFont.fnt");
    titleText->setAnchorPoint(CCPointMake(0.5, 1.0));
    titleText->setPosition(windowSize.width*0.5, (windowSize.height - height) * 0.5 + height - 15);
    titleText->setScale(0.9);
    m_mainLayer->addChild(titleText, 3);
    
    if (!m_containsBorder) {
        textArea->setPosition(scale9Pos + CCPointMake(0, 5));
    }
    
    m_buttonMenu = CCMenu::create();
    m_mainLayer->addChild(m_buttonMenu, 2);
    
    
    
    m_button1 = ButtonSprite::create(button1, 90, 0, 1.0, false);
    auto button1Menu = CCMenuItemSpriteExtra::create(m_button1, nullptr, this, SEL_MenuHandler(&FLAlertLayer::onBtn1));
    m_buttonMenu->addChild(button1Menu);
    
    
    CCMenuItemSpriteExtra* button2Menu;
    if (!button2) m_noAction = true;
    else {
        m_button2 = ButtonSprite::create(button2, 90, 0, 1.0, false);
        button2Menu = CCMenuItemSpriteExtra::create(m_button2, nullptr, this, SEL_MenuHandler(&FLAlertLayer::onBtn2));
        m_buttonMenu->addChild(button2Menu);
    }
    
    float menuLength = m_button1->getContentSize().width;
    menuLength += m_button2->getContentSize().width;
    auto menuCount = m_buttonMenu->getChildren()->count();
    if (menuCount > 1) {
        float padding = (width - menuLength) * 0.5;
        padding = std::min(padding, 15.0f);
        m_buttonMenu->alignItemsHorizontallyWithPadding(padding);
    }
    
    m_buttonMenu->setPosition(CCPointMake(windowSize.width * 0.5, (windowSize.height - height) * 0.5 + 30.0));
    
    return true;
}

void show() {
    if (!m_noElasticity) {
        m_mainLayer->setScale(0.1);
        auto scaleTo = CCScaleTo::create(0.5, 1);
        auto elasticOut = CCEaseElasticOut::create(scaleTo, 0.6);
        m_mainLayer->runAction(elasticOut);
    }
    
    int zOrder;
    auto runningScene = m_scene;
    if (!runningScene) {
        runningScene = CCDirector::sharedDirector()->getRunningScene();
        m_ZOrder = CCDirector::sharedDirector()->getRunningScene()->getHighestChildZ() + 1;
    }
    m_ZOrder = std::max(105, m_ZOrder);
    runningScene->addChild(this, m_ZOrder);
    
    if (!m_noElasticity) {
        auto oldOpacity = getOpacity();
        setOpacity(0);
        runAction(CCFadeTo::create(0.14, oldOpacity));
    }
    
    setVisible(true);
}

using namespace cocos2d;
 using namespace cocos2d::extension;
 
 class $(FLAlertLayer) {
	inline void sendAndCleanup(bool alert) {
 if (m_alertProtocol) m_alertProtocol->FLAlert_Clicked(this, alert);
 if (m_containsBorder) CCDirector::sharedDirector()->getTouchDispatcher()->setForcePrio(false);
 removeFromParentAndCleanup(true);
	}
	void constructor() {
 m_buttonMenu = nullptr;
 m_controlConnected = -1;
 m_mainLayer = nullptr;
 m_ZOrder = 0;
 m_noElasticity = false;
 m_reverseKeyBack = false;
 m_scene = nullptr;
 m_alertProtocol = nullptr;
 m_scrollingLayer = nullptr;
 m_button2 = nullptr;
 m_button1 = nullptr;
 m_joystickConnected = -1;
 m_containsBorder = 0;
 }
	static FLAlertLayer* create(FLAlertLayerProtocol* target, char const* title, gd::string caption, char const* button1, char const* button2) {
 return create(target, title, caption, button1, button2, 250.0, false, 0.0);
	}
	static FLAlertLayer* create(FLAlertLayerProtocol* target, char const* title, gd::string caption, char const* button1, char const* button2, float width) {
 return create(target, title, caption, button1, button2, width, false, 0.0);
	}
	static FLAlertLayer* create(FLAlertLayerProtocol* target, char const* title, gd::string caption, char const* button1, char const* button2, float width, bool border, float height) {
 auto ret = new FLAlertLayer();
 if (ret && ret->init(target, title, caption, button1, button2, width, border, height)) {
 ret->autorelease();
 return ret;
 }
 CC_SAFE_DELETE(ret);
 return NULL;
	}
	bool init(FLAlertLayerProtocol* target, char const* title, gd::string caption, char const* button1, char const* button2, float width, bool border, float height) {
 if (!cocos2d::CCLayerColor::initWithColor(ccc4(0,0,0,150))) return false;
 m_containsBorder = border;
 CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
 
 setTouchEnabled(true);
 setKeypadEnabled(true);
 setKeyboardEnabled(true);
 m_reverseKeyBack = false;
 m_alertProtocol = target;
 
 auto windowSize = CCDirector::sharedDirector()->getWinSize();
 
 m_mainLayer = cocos2d::CCLayer::create();
 addChild(m_mainLayer);
 
 TextArea* textArea;
 if (!m_containsBorder) {
 textArea = TextArea::create(caption, "chatFont.fnt", 1.0, width - 60.0, CCPointMake(0.5, 0.5), 20.0, false);
 m_mainLayer->addChild(textArea, 3);
 height = textArea->m_obRect.size.height + 120;
 height = std::max(height, 140.0f);
 }
 // honestly this is there but not added anywhere what
 // auto layerColor = CCLayerColor::create(ccc4(0,0,0,255), width, height);
 // auto layerColorPos = CCPointMake(windowSize.width - width, windowSize.height - height) * 0.5;
 // layerColor->setPosition(layerColorPos);
 // layerColor->setVisible(false);
 
 // auto layerColor2 = CCLayerColor::create(ccc4(150,150,150,255), width + 16, height + 16);
 // auto layerColor2Pos = layerColorPos - CCPointMake(8, 8);
 // layerColor2->setPosition(layerColor2Pos);
 // layerColor2->setVisible(false);
 
 auto scale9 = CCScale9Sprite::create("square01_001.png", CCRectMake(0, 0, 94, 94));
 scale9->setContentSize(CCSizeMake(width, height));
 auto scale9Pos = CCPointMake(windowSize.width*0.5, windowSize.height*0.5);
 scale9->setPosition(scale9Pos);
 m_mainLayer->addChild(scale9, 1);
 
 auto titleText = CCLabelBMFont::create(title, "goldFont.fnt");
 titleText->setAnchorPoint(CCPointMake(0.5, 1.0));
 titleText->setPosition(windowSize.width*0.5, (windowSize.height - height) * 0.5 + height - 15);
 titleText->setScale(0.9);
 m_mainLayer->addChild(titleText, 3);
 
 if (!m_containsBorder) {
 textArea->setPosition(scale9Pos + CCPointMake(0, 5));
 }
 
 m_buttonMenu = CCMenu::create();
 m_mainLayer->addChild(m_buttonMenu, 2);
 
 
 
 m_button1 = ButtonSprite::create(button1, 90, 0, 1.0, false);
 auto button1Menu = CCMenuItemSpriteExtra::create(m_button1, nullptr, this, SEL_MenuHandler(&FLAlertLayer::onBtn1));
 m_buttonMenu->addChild(button1Menu);
 
 
 CCMenuItemSpriteExtra* button2Menu;
 if (!button2) m_noAction = true;
 else {
 m_button2 = ButtonSprite::create(button2, 90, 0, 1.0, false);
 button2Menu = CCMenuItemSpriteExtra::create(m_button2, nullptr, this, SEL_MenuHandler(&FLAlertLayer::onBtn2));
 m_buttonMenu->addChild(button2Menu);
 }
 
 float menuLength = m_button1->getContentSize().width;
 menuLength += m_button2->getContentSize().width;
 auto menuCount = m_buttonMenu->getChildren()->count();
 if (menuCount > 1) {
 float padding = (width - menuLength) * 0.5;
 padding = std::min(padding, 15.0f);
 m_buttonMenu->alignItemsHorizontallyWithPadding(padding);
 }
 
 m_buttonMenu->setPosition(CCPointMake(windowSize.width * 0.5, (windowSize.height - height) * 0.5 + 30.0));
 
 // TODO: implement this
 //PlatformToolbox::isControllerConnected
 if (PlatformToolbox::isControllerConnected()) {
 auto nodeConvert1 = m_mainLayer->convertToNodeSpace(CCPointMake(windowSize.width*0.5, windowSize.height*0.5));
 auto nodeConvert2 = m_buttonMenu->convertToWorldSpace(button2Menu->getPosition());
 nodeConvert2 = m_mainLayer->convertToNodeSpace(nodeConvert2);
 
 auto midConvert = CCPointMake(nodeConvert1.x, nodeConvert2.y);
 
 auto controllerBSprite = CCSprite::createWithSpriteFrameName("controllerBtn_B_001.png");
 m_mainLayer->addChild(controllerBSprite, 10);
 controllerBSprite->setPosition(midConvert + CCPointMake(-116.0, 0.0));
 
 auto controllerXSprite = CCSprite::createWithSpriteFrameName("controllerBtn_X_001.png");
 m_mainLayer->addChild(controllerXSprite, 10);
 controllerXSprite->setPosition(midConvert + CCPointMake(116.0, 0.0));
 }
 
 m_controlConnected = -1;
 return true;
	}
	bool ccTouchBegan(CCTouch* touch, CCEvent* event) {
 if (m_buttonMenu) {
 if (m_controlConnected == -1 && m_buttonMenu->ccTouchBegan(touch, event)) {
 m_controlConnected = touch->getID();
 }
 }
 else if (m_scrollingLayer) {
 if (m_joystickConnected == -1 && m_scrollingLayer->ccTouchBegan(touch, event)) {
 m_joystickConnected = touch->getID();
 }
 }
 return true;
	}
	void ccTouchMoved(CCTouch* touch, CCEvent* event) {
 if (m_controlConnected == touch->getID()) {
 m_buttonMenu->ccTouchMoved(touch, event);
 }
 else if (m_joystickConnected == touch->getID()) {
 m_scrollingLayer->ccTouchMoved(touch, event);
 }
	}
	void ccTouchEnded(CCTouch* touch, CCEvent* event) {
 if (m_controlConnected == touch->getID()) {
 m_buttonMenu->ccTouchEnded(touch, event);
 m_controlConnected = -1;
 }
 else if (m_joystickConnected == touch->getID()) {
 m_scrollingLayer->ccTouchEnded(touch, event);
 m_joystickConnected = -1;
 }
	}
	void ccTouchCancelled(CCTouch* touch, CCEvent* event) {
 if (m_controlConnected == touch->getID()) {
 m_buttonMenu->ccTouchCancelled(touch, event);
 }
 else if (m_joystickConnected == touch->getID()) {
 m_scrollingLayer->ccTouchCancelled(touch, event);
 }
	}
	void keyBackClicked() {
 setKeypadEnabled(false);
 setKeyboardEnabled(false);
 sendAndCleanup(m_reverseKeyBack);
	}
	void registerWithTouchDispatcher() {
 int targetPrio;
 if (CCDirector::sharedDirector()->getTouchDispatcher()->getForcePrio()) {
 targetPrio = CCDirector::sharedDirector()->getTouchDispatcher()->getTargetPrio() - 1;
 }
 else targetPrio = -501;
 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, targetPrio, true);
	}
	void keyDown(enumKeyCodes keyCode) {
 if (keyCode == 0x3ec) sendAndCleanup(true);
 else if (keyCode == KEY_Space && !m_noAction) return;
 else CCLayer::keyDown(keyCode);
	}
	void onEnter() {
 CCDirector::sharedDirector()->getTouchDispatcher()->setForcePrio(true);
 CCLayer::onEnter();
	}
	void show() {
 if (!m_noElasticity) {
 m_mainLayer->setScale(0.1);
 auto scaleTo = CCScaleTo::create(0.5, 1);
 auto elasticOut = CCEaseElasticOut::create(scaleTo, 0.6);
 m_mainLayer->runAction(elasticOut);
 }
 
 int zOrder;
 auto runningScene = m_scene;
 if (!runningScene) {
 runningScene = CCDirector::sharedDirector()->getRunningScene();
 m_ZOrder = CCDirector::sharedDirector()->getRunningScene()->getHighestChildZ() + 1;
 }
 m_ZOrder = std::max(105, m_ZOrder);
 runningScene->addChild(this, m_ZOrder);
 
 if (!m_noElasticity) {
 auto oldOpacity = getOpacity();
 setOpacity(0);
 runAction(CCFadeTo::create(0.14, oldOpacity));
 }
 
 setVisible(true);
	}
	void onBtn1(cocos2d::CCObject*) {
 sendAndCleanup(false);
	}
	void onBtn2(cocos2d::CCObject*) {
 sendAndCleanup(true);
	}
 };*/