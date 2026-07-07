#ifndef __GARAGE_PAGE_H__
#define __GARAGE_PAGE_H__

#include "cocos2d.h"
#include "GJGarageLayer.h"

class GaragePage : public cocos2d::CCLayer {
public:
	static GaragePage* create(IconType type, GJGarageLayer* garage);
	bool init(IconType type, GJGarageLayer* garage);
	void onSelect(cocos2d::CCObject* sender);

	cocos2d::CCSprite* unk_0x118; // 0x118
};

#endif