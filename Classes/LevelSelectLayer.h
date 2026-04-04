#ifndef _LEVEL_SELECT_LAYER_H_
#define _LEVEL_SELECT_LAYER_H_

#include "cocos2d.h"
#include "BoomScrollLayer.h"

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
    void onPrev(CCObject* sender);
    void onNext(CCObject* sender);
protected:
	cocos2d::CCSprite* m_backgroundSprite; // 0x114
	cocos2d::CCSprite* m_ground; // 0x118
    BoomScrollLayer* m_scrollLayer; // 0x11c
};

#endif