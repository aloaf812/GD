	#ifndef _CCMENU_ITEM_SPRITE_EXTRA_H_
#define _CCMENU_ITEM_SPRITE_EXTRA_H_

#include "cocos2d.h"

class CCMenuItemSpriteExtra : public cocos2d::CCMenuItemSprite
{
public:
    CCMenuItemSpriteExtra();
    static CCMenuItemSpriteExtra* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
    virtual bool init(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
    void setSizeMult(float mult);
protected:
    float mScale;
    bool mUseAnimation;
    float mSelectedScale;
};
#endif