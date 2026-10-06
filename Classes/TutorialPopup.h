#ifndef __TUTORIAL_POPUP_H__
#define __TUTORIAL_POPUP_H__

#include "cocos2d.h"
#include "FLAlertLayer.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

class TutorialPopup : public FLAlertLayer {
public:
	bool init(std::string fileStr);
	void animateMenu();

	cocos2d::CCLayer* unk_0x1a0; // 0x1a0
	std::string unk_0x1a4; // 0x1a4
	CCMenuItemSpriteExtra* unk_0x1b4; // 0x1b4
};

#endif