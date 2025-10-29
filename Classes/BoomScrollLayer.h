#ifndef _BOOM_SCROLL_LAYER_H_
#define _BOOM_SCROLL_LAYER_H_

#include "cocos2d.h"

class BoomScrollLayerDelegate;

class BoomScrollLayer : public cocos2d::CCLayer {
public:
	BoomScrollLayer();
    static BoomScrollLayer* create(cocos2d::CCArray* pages, int param1, bool param2);
    virtual bool init();

    BoomScrollLayerDelegate* m_bslDelegate;
};

class BoomScrollLayerDelegate {
public:
    virtual void scrollLayerMoved(cocos2d::CCPoint p0);
    virtual void scrollLayerScrolledToPage(BoomScrollLayer* bsl, int p1);
    virtual void scrollLayerScrollingStarted(BoomScrollLayer* bsl);
};


#endif