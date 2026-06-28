// decompiled by ItzZyann
#include "FLAlertLayer.h"
#include "TextArea.h"
#include "ButtonSprite.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

USING_NS_CC;

void FLAlertLayerProtocol::FLAlert_Clicked(FLAlertLayer* layer, bool button2Clicked) { }

FLAlertLayer::FLAlertLayer() {
	CCLayerColor::create();
	m_buttonMenu = nullptr;
	m_controlTouchID = -1;
	m_zOrderPriority = 0;
	m_pParent = nullptr;
	m_targetScene = nullptr;
	m_reverseKeyBack = false;
	m_internalLayer = nullptr;
	m_touchTarget = nullptr;
	m_menuTouchActive = false;
}

FLAlertLayer* FLAlertLayer::create(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2) {
	return FLAlertLayer::create(protocol, title, caption, button1, button2, 250.0f);
}

FLAlertLayer* FLAlertLayer::create(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width) {
	FLAlertLayer* pRet = new FLAlertLayer();
	if (pRet && pRet->init(protocol, title, caption, button1, button2, width)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool FLAlertLayer::init(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width) {
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))) {
		return false;
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	m_pParent = protocol;
	m_reverseKeyBack = false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_internalLayer = CCLayer::create();
	this->addChild(m_internalLayer);

	TextArea* textArea = TextArea::create(caption, width - 60.0f, 0, ccp(0.5f, 0.5f), "chatFont.fnt");
	m_internalLayer->addChild(textArea, 3);

	float calculatedHeight = textArea->getContentSize().height + 100.0f;
	if (calculatedHeight <= 140.0f) {
		calculatedHeight = 140.0f;
	}

	CCLayerColor* dummyContentBg = CCLayerColor::create(ccc4(0, 0, 0, 255), width, calculatedHeight);
	dummyContentBg->setPosition(ccp((winSize.width - width) * 0.5f, (winSize.height - calculatedHeight) * 0.5f));
	dummyContentBg->setVisible(false);

	cocos2d::extension::CCScale9Sprite* bgSprite = cocos2d::extension::CCScale9Sprite::create("square01_001.png", CCRect(0, 0, 94, 94));
	bgSprite->setContentSize(CCSize(width, calculatedHeight));
	m_internalLayer->addChild(bgSprite, 1);
	bgSprite->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));

	CCLabelBMFont* titleLabel = CCLabelBMFont::create(title, "goldFont.fnt");
	titleLabel->setAnchorPoint(ccp(0.5f, 1.0f));
	titleLabel->setPosition(ccp(winSize.width * 0.5f, (calculatedHeight + dummyContentBg->getPositionY()) - 20.0f));
	m_internalLayer->addChild(titleLabel, 3);
	titleLabel->setScale(1.0f);

	textArea->setAnchorPoint(ccp(0.5f, 0.5f));
	textArea->setPosition(ccp(winSize.width * 0.5f, dummyContentBg->getPositionY() + (calculatedHeight * 0.5f) + 10.0f));

	m_buttonMenu = CCMenu::create();
	m_internalLayer->addChild(m_buttonMenu, 2);

	ButtonSprite* btnSprite1 = ButtonSprite::create(button1, 0, 1.0f, 0.0f, false);
	CCMenuItemSpriteExtra* menuItem1 = CCMenuItemSpriteExtra::create(btnSprite1, nullptr, this, menu_selector(FLAlertLayer::onBtn1));
	float cumulativeMenuWidth = menuItem1->getContentSize().width;
	m_buttonMenu->addChild(menuItem1);

	if (button2) {
		ButtonSprite* btnSprite2 = ButtonSprite::create(button2, 0, 1.0f, 0.0f, false);
		CCMenuItemSpriteExtra* menuItem2 = CCMenuItemSpriteExtra::create(btnSprite2, nullptr, this, menu_selector(FLAlertLayer::onBtn2));
		cumulativeMenuWidth += menuItem2->getContentSize().width;
		m_buttonMenu->addChild(menuItem2);
	}

	if (m_buttonMenu->getChildren() && m_buttonMenu->getChildren()->count() > 1) {
		float padding = (width - cumulativeMenuWidth) * 0.5f;
		if (padding >= 15.0f) {
			padding = 15.0f;
		}
		m_buttonMenu->alignItemsHorizontallyWithPadding(padding);
	}

	m_buttonMenu->setPosition(ccp(winSize.width * 0.5f, dummyContentBg->getPositionY() + 30.0f));

	m_controlTouchID = -1;
	return true;
}

void FLAlertLayer::show() {
	GLubyte originalOpacity = this->getOpacity();
	m_internalLayer->setScale(0.5f);

	CCEaseElasticOut* bounceOpenAction = CCEaseElasticOut::create(CCScaleTo::create(0.5f, 1.0f), 0.6f);
	m_internalLayer->runAction(bounceOpenAction);

	CCNode* renderingContext = m_targetScene;
	if (!renderingContext) {
		renderingContext = CCDirector::sharedDirector()->getRunningScene();
	}
	if (m_zOrderPriority == 0) {
		m_zOrderPriority = 105;
	}

	renderingContext->addChild(this, m_zOrderPriority);
	this->setVisible(true);

	CCFadeTo* fadeInBg = CCFadeTo::create(0.14f, originalOpacity);
	this->runAction(fadeInBg);

	this->setTouchEnabled(true);
}

void FLAlertLayer::onBtn1(CCObject* sender) {
	this->setTouchEnabled(false);
	if (m_pParent) {
		m_pParent->FLAlert_Clicked(this, false);
	}
	this->removeFromParentAndCleanup(true);
}

void FLAlertLayer::onBtn2(CCObject* sender) {
	this->setTouchEnabled(false);
	if (m_pParent) {
		m_pParent->FLAlert_Clicked(this, true);
	}
	this->removeFromParentAndCleanup(true);
}

void FLAlertLayer::keyBackClicked() {
	if (m_reverseKeyBack) {
		this->onBtn2(nullptr);
	}
	else {
		this->onBtn1(nullptr);
	}
}

void FLAlertLayer::registerWithTouchDispatcher() {
	CCTouchDispatcher* dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this, -500, true);
}

bool FLAlertLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	if (m_buttonMenu && m_buttonMenu->isVisible() && m_buttonMenu->ccTouchBegan(touch, event)) {
		m_menuTouchActive = true;
		return true;
	}
	m_menuTouchActive = false;

	if (m_controlTouchID == -1) {
		if (m_touchTarget) {
			if (static_cast<CCLayer*>(m_touchTarget)->ccTouchBegan(touch, event)) {
				m_controlTouchID = touch->getID();
			}
		}
	}

	return true;
}

void FLAlertLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	if (m_menuTouchActive && m_buttonMenu) {
		m_buttonMenu->ccTouchMoved(touch, event);
	}

	if (m_controlTouchID == touch->getID()) {
		if (m_touchTarget) {
			static_cast<CCLayer*>(m_touchTarget)->ccTouchMoved(touch, event);
		}
	}
}

void FLAlertLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
	if (m_menuTouchActive && m_buttonMenu) {
		m_buttonMenu->ccTouchCancelled(touch, event);
		m_menuTouchActive = false;
	}

	if (m_controlTouchID == touch->getID()) {
		if (m_touchTarget) {
			static_cast<CCLayer*>(m_touchTarget)->ccTouchCancelled(touch, event);
		}
	}
}

void FLAlertLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
	if (m_menuTouchActive && m_buttonMenu) {
		m_buttonMenu->ccTouchEnded(touch, event);
		m_menuTouchActive = false;
	}

	if (m_controlTouchID == touch->getID()) {
		if (m_touchTarget) {
			static_cast<CCLayer*>(m_touchTarget)->ccTouchEnded(touch, event);
		}
		m_controlTouchID = -1;
	}
}