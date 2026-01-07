#ifndef _BOOM_SCROLL_LAYER_H_
#define _BOOM_SCROLL_LAYER_H_

#include "cocos2d.h"
#include "ExtendedLayer.h"

class BoomScrollLayerDelegate;

class BoomScrollLayer : public cocos2d::CCLayer {
public:
	BoomScrollLayer();
    static BoomScrollLayer* create(cocos2d::CCArray* pages, int param1, bool param2);
    virtual bool init(cocos2d::CCArray* pages, int param1, bool param2);
    void updateDots(float);
    void updatePages();
    void quickUpdate();
    void moveToPage(int page);
    CC_PROPERTY_READONLY(int, m_currentScreen, CurrentScreen);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
protected:
    ExtendedLayer* m_extendedLayer;
    BoomScrollLayerDelegate* m_bslDelegate;
    cocos2d::CCArray* m_pageDots;
    cocos2d::CCArray* m_pages;
};

class BoomScrollLayerDelegate {
public:
    virtual void scrollLayerMoved(cocos2d::CCPoint p0);
    virtual void scrollLayerScrolledToPage(BoomScrollLayer* bsl, int p1);
    virtual void scrollLayerScrollingStarted(BoomScrollLayer* bsl);
};


#endif