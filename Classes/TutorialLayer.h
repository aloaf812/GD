#ifndef __TUTORIAL_LAYER_H__
#define __TUTORIAL_LAYER_H__

#include "cocos2d.h"
#include "FLAlertLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

class TutorialLayer : public FLAlertLayer {
public:
	CREATE_FUNC(TutorialLayer);
	bool init();
	void removeTutorialTexture();

	cocos2d::CCMenu* unk_0x188; // 0x188
	cocos2d::CCLayer* unk_0x1a0; // 0x1a0
	cocos2d::CCLayer* unk_0x1a4; // 0x1a4
	int unk_0x1a8; // 0x1a8
	CCMenuItemSpriteExtra* unk_0x1ac; // 0x1ac
	CCMenuItemSpriteExtra* unk_0x1b0; // 0x1b0
};

#endif /* defined(__TUTORIAL_LAYER_H__) */
