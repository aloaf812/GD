// decompiled by ItzZyann
#ifndef _FL_ALERT_LAYER_H_
#define _FL_ALERT_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class FLAlertLayer;

class FLAlertLayerProtocol {
public:
	virtual void FLAlert_Clicked(FLAlertLayer* layer, bool button2Clicked);
};

class FLAlertLayer : public cocos2d::CCLayerColor {
public:
	FLAlertLayer();

	static FLAlertLayer* create(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2);
	static FLAlertLayer* create(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width);

	bool init(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width);

	virtual void show();
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	virtual void registerWithTouchDispatcher();
	virtual void keyBackClicked();

	void onBtn1(cocos2d::CCObject* sender);
	void onBtn2(cocos2d::CCObject* sender);

	cocos2d::CCMenu* m_buttonMenu; // 0x188
	int m_controlTouchID; // 0x18c
	int m_zOrderPriority; // 0x190

	// not in the code, will be removed soon
	cocos2d::CCObject* m_touchTarget;
	bool m_menuTouchActive;

	CC_SYNTHESIZE(FLAlertLayerProtocol*, m_pParent, PParent); // 0x194
	CC_SYNTHESIZE(cocos2d::CCNode*, m_targetScene, TargetScene); // 0x198
	CC_SYNTHESIZE(bool, m_reverseKeyBack, ReverseKeyBack); // 0x19c
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_internalLayer, InternalLayer); // 0x1a8
};

#endif