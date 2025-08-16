#include "CCMenuItemSpriteExtra.h"

USING_NS_CC;

CCMenuItemSpriteExtra::CCMenuItemSpriteExtra()
{
    mScale = 0.0f;
    mSelectedScale = 1.0f;
    mUseAnimation = false;
    /* mDarken = false;
    mUnknownSFXValue = 1.0f;
    mSelectSound = "";
    mHoverSound = "";
    mDarkenAmount = 0.78431f;
    mOffsetPositionSelected = CCPoint();
    mSelectDuration = 0.3f;
    mUnselectDuration = 0.4f;
    mAnimationType = MENU_ANIM_TYPE_SCALE;
    mOffsetPosition = CCPoint(); */
}

CCMenuItemSpriteExtra* CCMenuItemSpriteExtra::create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector)
{
    CCMenuItemSpriteExtra* pRet = new CCMenuItemSpriteExtra();
    if (pRet && pRet->init(normalSprite, selectedSprite, target, selector))
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

bool CCMenuItemSpriteExtra::init(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector)
{
    if (!CCMenuItemSprite::initWithNormalSprite(normalSprite, selectedSprite, NULL, target, selector))
        return false;
    
    this->mScale = 1.0f;
    normalSprite->setAnchorPoint(CCPoint(0.5f, 0.5f));
    
    CCSize size = normalSprite->getContentSize();
    this->setContentSize(CCSize(size.width * normalSprite->getScaleX(), size.height));
    
    normalSprite->setPosition(normalSprite->getParent()->convertToNodeSpace(CCPoint(0.0f, 0.0f)));
    
    //this->mDarken = true;
    this->mUseAnimation = true;
    this->mSelectedScale = 1.26f;
    
    return true;
}

void CCMenuItemSpriteExtra::setSizeMult(float mult)
{
    CCNode* normalImage = this->getNormalImage();
    if (!normalImage)
        return;
    
    CCSize oldSize = this->getContentSize();
    CCSize imgSize = normalImage->getContentSize();
    
    float sizeX = imgSize.width * normalImage->getScaleX() * mult;
    float sizeY = imgSize.height * normalImage->getScaleY() * mult;
    
    CCSize newSize(sizeX, sizeY);
    
    this->setContentSize(newSize);
    
    CCSize sz(newSize.width - oldSize.width, newSize.height - oldSize.height);
    normalImage->setPosition(normalImage->getPosition() + CCPoint(sz.width * 0.5f, sz.height * 0.5f));
}