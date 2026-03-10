// Decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/TextArea.cpp
#include "TextArea.h"
USING_NS_CC;

bool TextArea::init(char const* str, float scale, int order, cocos2d::CCPoint align, char const* unk3, float unk4)
{
    if (!CCSprite::init())
        return false;
    
	m_order = order;
	m_scale = scale;

    return true;
}

TextArea* TextArea::create(char const* str, float scale, int order, cocos2d::CCPoint align, char const* unk3, float unk4)
{
    TextArea* pRet = new TextArea();
	if (pRet && pRet->init(str, scale, order, align, unk3, unk4))
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