#include "GJListLayer.h"
USING_NS_CC;

GJListLayer* GJListLayer::create(BoomListView *p0, const char *p1, ccColor4B color, float width, float height)
{
    GJListLayer* pRet = new GJListLayer();
    pRet->init(color, width, height);
    return NULL;
}

GJListLayer::GJListLayer()
{
    
}

bool GJListLayer::init(ccColor4B color, float width, float height)
{
    if (!CCLayerColor::initWithColor(color, width, height))
        return false;
    
    return true;
}