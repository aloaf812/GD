// Decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/TextArea.cpp
#include "TextArea.h"
USING_NS_CC;

bool TextArea::init(std::string str, const char* font, float separation, float width, cocos2d::CCPoint anchor, float lineSeparation, bool plainText)
{
    if (!CCSprite::init())
        return false;
    
    return true;
}

TextArea* TextArea::create(std::string str, const char* font, float separation, float width, cocos2d::CCPoint anchor, float lineSeparation, bool plainText)
{
    TextArea* pRet = new TextArea();
    if (pRet && pRet->init(str, font, separation, width, anchor, lineSeparation, plainText))
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