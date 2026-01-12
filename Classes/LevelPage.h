#ifndef __GeometryDash__LevelPage__
#define __GeometryDash__LevelPage__

#include "cocos2d.h"
#include "GJGameLevel.h"
#include <algorithm>

class LevelPage : public cocos2d::CCLayer {
    GJGameLevel* m_level;
public:
    static LevelPage* create(GJGameLevel* level);
    bool init(GJGameLevel* level);
    void onFacebook(cocos2d::CCObject* sender);
    void onPlay(cocos2d::CCObject* sender);
};

#endif /* defined(__GeometryDash__LevelPage__) */
