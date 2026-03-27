#ifndef __GeometryDash__LevelPage__
#define __GeometryDash__LevelPage__

#include "cocos2d.h"
#include "GJGameLevel.h"
#include <algorithm>

class LevelPage : public cocos2d::CCLayer {
    GJGameLevel* m_level; // 0x110
	cocos2d::CCMenu* field_0x114; // 0x114
public:
    static LevelPage* create(GJGameLevel* level);
    bool init(GJGameLevel* level);
    void onInfo(cocos2d::CCObject* sender);
    void onPlay(cocos2d::CCObject* sender);
};

#endif /* defined(__GeometryDash__LevelPage__) */
