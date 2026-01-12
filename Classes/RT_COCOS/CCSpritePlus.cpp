// Decompiled by CallocGD: https://github.com/CallocGD/GD-2.205-Decompiled/blob/main/GD/code/src/CCSpritePlus.cpp
#include "CCSpritePlus.h"
USING_NS_CC;

void CCSpritePlus::addFollower(cocos2d::CCNode * sprite){
    m_hasFollower = true;
    if (m_followers == nullptr) {
        m_followers = cocos2d::CCArray::create();
        m_followers->retain();
    }
    m_followers->addObject(sprite);
}


CCSpritePlus* CCSpritePlus::createWithSpriteFrame(cocos2d::CCSpriteFrame* frame){
    CCSpritePlus* sprite = new CCSpritePlus;
    if ((frame != nullptr) && (sprite->initWithSpriteFrame(frame))){
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

CCSpritePlus* CCSpritePlus::createWithSpriteFrameName(const char* name){
    return createWithSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
}

void CCSpritePlus::followSprite(CCSpritePlus *sprite){
    m_followingSprite = sprite;
    sprite->addFollower(this);
}

/* This is where the fun begins... */


cocos2d::CCSprite * CCSpritePlus::getFollower(){   
    if (m_hasFollower != false){
        return reinterpret_cast<cocos2d::CCSprite *>(m_followers->objectAtIndex(0));
    }
    return nullptr;
}


bool CCSpritePlus::initWithSpriteFrameName(char const* name){
    m_eObjType = 13;
    return cocos2d::CCSprite::initWithSpriteFrameName(name);
}

bool CCSpritePlus::initWithTexture(cocos2d::CCTexture2D *texture){
    m_eObjType = 13;
    return cocos2d::CCSprite::initWithTexture(texture);
}

void CCSpritePlus::removeFollower(CCNode *sprite){
    if (m_followers != nullptr) {
        m_followers->removeObject(sprite,true);
        if (m_followers->count() == 0) {
            m_hasFollower = false;
        }
    }
}

void CCSpritePlus::setFlipX(bool value){
    unsigned int i;
    cocos2d::CCSprite::setFlipX(value);
    if ((m_propagateFlipChanges != false) && (m_pParent != nullptr)) {
        for (i= 0; i < m_pParent->getChildrenCount(); i++) {
            (reinterpret_cast<cocos2d::CCSprite*>(m_pParent->getChildren()->objectAtIndex(i)))->setFlipX(value);
        }
    }
    if (m_hasFollower) {
        for (i = 0; i < m_followers->count(); i++) {
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setFlipX(value);
        }
    }
}


void CCSpritePlus::setFlipY(bool value){
    unsigned int i;
    cocos2d::CCSprite::setFlipY(value);
    if ((m_propagateFlipChanges != false) && (m_pParent != nullptr)) {
        for (i= 0; i < m_pParent->getChildrenCount(); i++) {
            (reinterpret_cast<cocos2d::CCSprite*>(m_pParent->getChildren()->objectAtIndex(i)))->setFlipY(value);
        }
    }
    if (m_hasFollower) {
        for (i = 0; i < m_followers->count(); i++) {
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setFlipY(value);
        }
    }
}


/* It is likely Robtop actually used a macro on all of these so I will be making my own Macro as well and then Expanding all of them so you can read them all */
#define CCSPRITEPLUS_SET_THING(TYPE, VALUE, CALLNAME) \
    void CCSpritePlus::set##CALLNAME(TYPE VALUE){\
        cocos2d::CCSprite::set##CALLNAME(VALUE);\
        if (m_hasFollower){ \
            for (unsigned int i = 0;  i < m_followers->count(); i++){\
                reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->set##CALLNAME(VALUE);\
            } \
        } \
    }


void CCSpritePlus::setPosition(cocos2d::CCPoint const &pos){
    cocos2d::CCSprite::setPosition(pos);
    /*if (m_hasFollower) {
        for (unsigned int i = 0;  i < m_followers->count(); i++){
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setPosition(pos);
        }
    }*/
}



void CCSpritePlus::setRotation(float fRotation){
    cocos2d::CCSprite::setRotation(fRotation);
    /*if (m_hasFollower) {
        for (unsigned int i = 0;  i < m_followers->count(); i++){
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setRotation(fRotation);
        }
    }*/
}

void CCSpritePlus::setRotationX(float fRotationX){ 
    cocos2d::CCSprite::setRotationX(fRotationX); 
    if (m_hasFollower){ 
        for (unsigned int i = 0; i < m_followers->count(); i++){ 
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setRotationX(fRotationX); 
        } 
    } 
}

void CCSpritePlus::setRotationY(float fRoationY){ 
    cocos2d::CCSprite::setRotationY(fRoationY); 
    if (m_hasFollower){ 
        for (unsigned int i = 0; i < m_followers->count(); i++){ reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setRotationY(fRoationY); 
        }
    } 
}

void CCSpritePlus::setScale(float fScale){ 
    cocos2d::CCSprite::setScale(fScale); 
    if (m_hasFollower){ 
        for (unsigned int i = 0; i < m_followers->count(); i++){ 
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setScale(fScale); 
        } 
    }
}

void CCSpritePlus::setScaleX(float fScaleX){ 
    cocos2d::CCSprite::setScaleX(fScaleX); 
    /*if (m_hasFollower){ 
        for (unsigned int i = 0; i < m_followers->count(); i++){ 
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setScaleX(fScaleX); 
        } 
    }*/ 
}

void CCSpritePlus::setScaleY(float fScaleY){ 
    cocos2d::CCSprite::setScaleY(fScaleY); 
	/*if (m_hasFollower){
        for (unsigned int i = 0; i < m_followers->count(); i++){ 
            reinterpret_cast<cocos2d::CCSprite*>(m_followers->objectAtIndex(i))->setScaleY(fScaleY); 
        } 
    } */
}

void CCSpritePlus::stopFollow(){
    if (m_followingSprite != nullptr){
        m_followingSprite->removeFollower(this);
    }
}