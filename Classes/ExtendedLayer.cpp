#include "ExtendedLayer.h"
USING_NS_CC;
ExtendedLayer* ExtendedLayer::create()
{
    ExtendedLayer* pRet = new ExtendedLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ExtendedLayer::init()
{   
    return CCLayer::init();
}