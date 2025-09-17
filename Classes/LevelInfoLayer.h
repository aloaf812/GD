#ifndef _LEVEL_INFO_LAYER_H
#define _LEVEL_INFO_LAYER_H

#include "cocos2d.h"
#include "GJGameLevel.h"

class LevelInfoLayer : public cocos2d::CCLayer {
public:
    LevelInfoLayer();
    static LevelInfoLayer* create(GJGameLevel* level);
    static cocos2d::CCScene* scene(GJGameLevel* level);
    bool init(GJGameLevel* level);
    void onPlay(cocos2d::CCObject* sender);
    void onBack(cocos2d::CCObject* sender);
protected:
    GJGameLevel* m_level;
    
};

#endif /* defined(_LEVEL_INFO_LAYER_H) */
