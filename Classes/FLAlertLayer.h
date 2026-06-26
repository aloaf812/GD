// decompiled by ItzZyann
// from GD 1.71 binary

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
	virtual ~FLAlertLayer();

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

	CC_SYNTHESIZE(FLAlertLayerProtocol*, m_pParent, PParent);
	CC_SYNTHESIZE(cocos2d::CCNode*, m_targetScene, TargetScene);
	CC_SYNTHESIZE(bool, m_reverseKeyBack, ReverseKeyBack);
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_internalLayer, InternalLayer);

protected:
	cocos2d::CCMenu* m_buttonMenu;
	int m_controlTouchID;
	int m_zOrderPriority;
	cocos2d::CCObject* m_touchTarget;
	bool m_menuTouchActive;
};

#endif