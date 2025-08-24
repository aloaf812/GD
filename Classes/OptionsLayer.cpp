#include "OptionsLayer.h"
USING_NS_CC;

OptionsLayer* OptionsLayer::create()
{
    OptionsLayer* pRet = new OptionsLayer();
    if (pRet && pRet->GJDropDownLayer::init("Options", 100.0f))
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