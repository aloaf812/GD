#ifndef __GJ_GARAGE_LAYER_H__
#define __GJ_GARAGE_LAYER_H__

#include "cocos2d.h"
#include "SimplePlayer.h"

class GJGarageLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    static GJGarageLayer* node();
    virtual bool init();

	void updatePlayerColors();
    void onBack(CCObject* sender);
protected:
    cocos2d::CCSprite* m_backgroundSprite;
	SimplePlayer* m_playerObject;
};
#endif