#include "BoomScrollLayer.h"
USING_NS_CC;

// BoomScrollLayerDelegate because being in a single file is cleaner

void BoomScrollLayerDelegate::scrollLayerMoved(cocos2d::CCPoint p0)
{

}

void BoomScrollLayerDelegate::scrollLayerScrolledToPage(BoomScrollLayer* bsl, int p1)
{

}

void BoomScrollLayerDelegate::scrollLayerScrollingStarted(BoomScrollLayer* bsl)
{
    
}

// now for the real BoomScrollLayer code
BoomScrollLayer::BoomScrollLayer()
{
    this->m_bslDelegate = nullptr;
}

BoomScrollLayer* BoomScrollLayer::create(cocos2d::CCArray* pages, int param1, bool param2)
{
    BoomScrollLayer* ret = new BoomScrollLayer();
    if (ret) {
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
    }

    return NULL;
}

bool BoomScrollLayer::init()
{
	return true;
}