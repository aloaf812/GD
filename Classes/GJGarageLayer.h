#ifndef __GJ_GARAGE_LAYER_H__
#define __GJ_GARAGE_LAYER_H__

#include "cocos2d.h"

class GJGarageLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static GJGarageLayer* node();
    virtual bool init();
    void onBack(CCObject* sender);
};
#endif