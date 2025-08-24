#ifndef __GeometryDash__CreatorLayer__
#define __GeometryDash__CreatorLayer__

#include "cocos2d.h"

class CreatorLayer : public cocos2d::CCLayer
{
public:
    CreatorLayer();
    static cocos2d::CCScene* scene();
    static CreatorLayer* create();
    bool init();
    void onBack(cocos2d::CCObject* sender);
};

#endif /* defined(__GeometryDash__CreatorLayer__) */
