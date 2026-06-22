#ifndef __GJ_GARAGE_LAYER_H__
#define __GJ_GARAGE_LAYER_H__

#include "cocos2d.h"
#include "SimplePlayer.h"
#include "RT_COCOS/CCMenuItemToggler.h"

class GJGarageLayer : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
	NODE_FUNC(GJGarageLayer);
    virtual bool init();

	void setupIconSelect();

	void updatePlayerColors();
    void onBack(CCObject* sender);
	void onSelectTab(CCObject* sender);
	void selectPage(IconType type);

	SimplePlayer* m_playerObject; // 0x118

	cocos2d::CCSprite* unk_0x120; // 0x120
	cocos2d::CCSprite* unk_0x124; // 0x124


	cocos2d::CCArray* unk_0x130; // 0x130

	CCMenuItemToggler* unk_0x13c; // 0x13c
	CCMenuItemToggler* unk_0x140; // 0x140
	CCMenuItemToggler* unk_0x144; // 0x144
	CCMenuItemToggler* unk_0x148; // 0x148
	CCMenuItemToggler* unk_0x14c; // 0x14c

	CC_SYNTHESIZE(cocos2d::CCSprite*, m_rateSprite, RateSprite); // 0x150
};
#endif