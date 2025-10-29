#include "GJListLayer.h"
USING_NS_CC;

GJListLayer* GJListLayer::create(BoomListView *p0, const char *p1, ccColor4B color, float width, float height)
{
    GJListLayer* pRet = new GJListLayer();
    
    if (pRet && pRet->init(color, width, height)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

GJListLayer::GJListLayer()
{
    
}

bool GJListLayer::init(ccColor4B color, float width, float height)
{
    if (!CCLayerColor::initWithColor(color, width, height))
        return false;
    
    CCSprite* bottomTableSpr = CCSprite::createWithSpriteFrameName("GJ_table_bottom_001.png");
    // bottomTableSpr->setPosition();

    return true;
}