// decompiled by ItzZyann
// from GD 1.71 binary

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
	void setFrames(const char* layer1, const char* layer2, const char* birdDome, const char* glow);
	void setColor(cocos2d::ccColor3B const& color);
	void setSecondColor(cocos2d::ccColor3B const& color);
	void updateColors();

protected:
	cocos2d::CCSprite* m_firstLayer; // 0x1b8  (+110)
	cocos2d::CCSprite* m_secondLayer; // 0x1bc  (+111)
	cocos2d::CCSprite* m_birdDome; // 0x1c0  (+112)
	cocos2d::CCSprite* m_outlineLayer; // 0x1c4  (+113)
	CC_SYNTHESIZE(int, m_special, Special); // 0x1c8  (+114)
};

#endif