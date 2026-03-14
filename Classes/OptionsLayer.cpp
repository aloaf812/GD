#include "OptionsLayer.h"
USING_NS_CC;

OptionsLayer* OptionsLayer::create()
{
    OptionsLayer* pRet = new OptionsLayer();
    if (pRet && pRet->init("Options"))
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

void OptionsLayer::customSetup()
{

}