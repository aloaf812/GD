#ifndef _SIMPLE_PLAYER_H
#define _SIMPLE_PLAYER_H

#include "cocos2d.h"
#include <stdio.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <algorithm>
#endif

enum class IconType {
    Cube = 0,
    Ship = 1,
    Ball = 2,
    UFO = 3,
    Special = 99
};

class SimplePlayer : public cocos2d::CCSprite {
public:
    SimplePlayer();
    static SimplePlayer* create(int iconID);
    bool init(int iconID);
	void updatePlayerFrame(int iconID, IconType type);
	void setSecondColor(cocos2d::ccColor3B const& color);
protected:
	cocos2d::CCSprite* m_firstLayer;
	cocos2d::CCSprite* m_secondLayer;
	cocos2d::CCSprite* m_outlineLayer;
    // CC_PROPERTY(int, m_special, Special);
};

#endif