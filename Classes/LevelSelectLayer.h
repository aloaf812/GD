#ifndef _LEVEL_SELECT_LAYER_H_
#define _LEVEL_SELECT_LAYER_H_

#include "cocos2d.h"

class LevelSelectLayer : public cocos2d::CCLayer
{
public:
    LevelSelectLayer();
    static cocos2d::CCScene* scene(int page);
    static LevelSelectLayer* create(int page);
    bool init(int page);
    void onDownload(CCObject* sender);
    void onBack(CCObject* sender);
    void onInfo(CCObject* sender);
    // void onPrev(CCObject* sender);
protected:
    cocos2d::CCSprite* m_backgroundSprite;
    struct colors;
};

#endif