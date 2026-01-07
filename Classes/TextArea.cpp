// Decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/TextArea.cpp
#include "TextArea.h"
USING_NS_CC;

bool TextArea::init(char const* str, float unk1, int unk2, cocos2d::CCPoint position, char const* unk3, float unk4)
{
    if (!CCSprite::init())
        return false;
    
    return true;
}

TextArea* TextArea::create(char const* str, float unk1, int unk2, cocos2d::CCPoint position, char const* unk3, float unk4)
{
    TextArea* pRet = new TextArea();
    if (pRet && pRet->init(str, unk1, unk2, position, unk3, unk4))
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