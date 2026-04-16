// Decompiled by CallocGD: https://github.com/CallocGD/GD-2.205-Decompiled/blob/main/GD/code/headers/CCSpritePlus.h
#ifndef __CCSPRITEPLUS_H__
#define __CCSPRITEPLUS_H__

#include "cocos2d.h"

/* Core Component in all GameObjects */
class CCSpritePlus : public cocos2d::CCSprite {

public:
	cocos2d::CCArray* m_followers; // 0x1b8
	CCSpritePlus* m_followingSprite; // 0x1bc
	bool m_hasFollower; // 0x1c0

	void addFollower(cocos2d::CCNode* sprite);
	
    static CCSpritePlus* createWithSpriteFrame(cocos2d::CCSpriteFrame* frame);
    static CCSpritePlus* createWithSpriteFrameName(char const* frame);
	void followSprite(CCSpritePlus* sprite);
    
	
    cocos2d::CCSprite * getFollower();
    bool initWithSpriteFrameName(char const* name);
    bool initWithTexture (cocos2d::CCTexture2D * texture);
    void removeFollower(cocos2d::CCNode* sprite);
    
    /* -- overrides -- */

    void setFlipX(bool value);
    void setFlipY(bool value);
    void setPosition(cocos2d::CCPoint const &pos);
	void setRotation(float fRotation);
    void setScale(float fScale);
    void setScaleX(float fScaleX);
    void setScaleY(float fScaleY);

    void stopFollow();
};

#endif // __CCSPRITEPLUS_H__