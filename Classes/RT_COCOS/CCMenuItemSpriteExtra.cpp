// decompiled by ProjectReversio: https://github.com/ProjectReversio/GeometryDash/blob/master/GeometryDash/Classes/CCMenuItemSpriteExtra.cpp
#include "CCMenuItemSpriteExtra.h"

USING_NS_CC;

CCMenuItemSpriteExtra::CCMenuItemSpriteExtra()
{
    mScale = 0.0f;
    mSelectedScale = 1.0f;
    mUseAnimation = false;
    mDarken = false;
    mUnknownSFXValue = 1.0f;
    mSelectSound = "";
    mHoverSound = "";
    mDarkenAmount = 0.78431f;
    mOffsetPositionSelected = CCPoint();
    mSelectDuration = 0.3f;
    mUnselectDuration = 0.4f;
    mAnimationType = MENU_ANIM_TYPE_SCALE;
    mOffsetPosition = CCPoint();
}

CCMenuItemSpriteExtra::~CCMenuItemSpriteExtra()
{
    
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

void CCMenuItemSpriteExtra::activate()
{
    if (!this->isEnabled())
        return;

    this->stopAllActions();
    if (this->mAnimationType == MENU_ANIM_TYPE_SCALE)
        this->setScale(mScale);

    if (!this->mSelectSound.empty())
    {
        // TODO: Missing GameSoundManager
        //GameSoundManager* pSoundManager = GameSoundManager::sharedManager();
        //pSoundManager->playEffect(this->mSelectSound, 1.0f, 0.0f, this->mUnknownSFXValue);
    }

    CCMenuItem::activate();
}

void CCMenuItemSpriteExtra::selected()
{
    if (!this->isEnabled())
        return;

    CCMenuItemSprite::selected();

    if (!mHoverSound.empty())
    {
        // TODO: Missing GameSoundManager
        //GameSoundManager* pSoundManager = GameSoundManager::sharedManager();
        //pSoundManager->playEffect(this->mHoverSound, 1.0f, 0.0f, this->mUnknownSFXValue);
    }

    if (mDarken)
    {
        unsigned char color = this->mDarkenAmount * 255.0f;
        CCSprite* sprite = (CCSprite*)this->getNormalImage();
        ccColor3B c = {color, color, color};
        sprite->setColor(c);
    }

    if (mUseAnimation)
    {
        switch (mAnimationType)
        {
            case MENU_ANIM_TYPE_MOVE:
            {
                CCNode* node = this->getNormalImage();
                node->stopActionByTag(0);
                CCMoveTo* moveTo = CCMoveTo::create(mSelectDuration, mOffsetPosition + mOffsetPositionSelected);
                CCEaseInOut* ease = CCEaseInOut::create(moveTo, 1.5f);
                ease->setTag(0);
                node->runAction(ease);
                break;
            }
            case MENU_ANIM_TYPE_SCALE:
            {
                this->stopActionByTag(0);
                CCScaleTo* scaleTo = CCScaleTo::create(mSelectDuration, mScale * mSelectedScale);
                CCEaseBounceOut* ease = CCEaseBounceOut::create(scaleTo);
                ease->setTag(0);
                this->runAction(ease);
                break;
            }
        }
    }
}

void CCMenuItemSpriteExtra::unselected()
{
    if (!this->isEnabled())
        return;

    CCMenuItemSprite::unselected();

    if (mDarken)
    {
        CCSprite* sprite = (CCSprite*)this->getNormalImage();
        sprite->setColor(ccWHITE);
    }

    if (mUseAnimation)
    {
        switch (mAnimationType)
        {
            case MENU_ANIM_TYPE_MOVE:
            {
                CCNode* node = this->getNormalImage();
                node->stopActionByTag(0);
                CCMoveTo* moveTo = CCMoveTo::create(mUnselectDuration, mOffsetPosition);
                CCEaseInOut* ease = CCEaseInOut::create(moveTo, 2.0f);
                ease->setTag(0);
                node->runAction(ease);
                break;
            }
            case MENU_ANIM_TYPE_SCALE:
            {
                this->stopActionByTag(0);
                CCScaleTo* scaleTo = CCScaleTo::create(mUnselectDuration, mScale);
                CCEaseBounceOut* ease = CCEaseBounceOut::create(scaleTo);
                ease->setTag(0);
                this->runAction(ease);
                break;
            }
        }
    }
}

void CCMenuItemSpriteExtra::setSizeMult(float size)
{
    CCNode* normalImage = this->getNormalImage();
    if (!normalImage)
        return;

    CCSize oldSize = this->getContentSize();
    CCSize imgSize = normalImage->getContentSize();

    float sizeX = imgSize.width * normalImage->getScaleX() * size;
    float sizeY = imgSize.height * normalImage->getScaleY() * size;

    CCSize newSize(sizeX, sizeY);

    this->setContentSize(newSize);

    CCSize sz(newSize.width - oldSize.width, newSize.height - oldSize.height);
    normalImage->setPosition(normalImage->getPosition() + CCPoint(sz.width * 0.5f, sz.height * 0.5f));
}

void CCMenuItemSpriteExtra::useAnimationType(MenuAnimationType type)
{
    this->mOffsetPosition = this->getNormalImage()->getPosition();
    this->mAnimationType = type;
}
