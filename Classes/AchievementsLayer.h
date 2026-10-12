#ifndef _ACHIEVEMENTS_LAYER_H_
#define _ACHIEVEMENTS_LAYER_H_

#include "cocos2d.h"
#include "GJDropDownLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

class AchievementsLayer : public GJDropDownLayer {
public:
	static AchievementsLayer* create();
	void customSetup();

	int unk_0x1a8; // 0x1a8
	CCMenuItemSpriteExtra* unk_0x1ac; // 0x1ac
	CCMenuItemSpriteExtra* unk_0x1b0; // 0x1b0

};

#endif /* __ACHIEVEMENTS_LAYER_H__ */