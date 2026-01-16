#ifndef _UI_LAYER_H
#define _UI_LAYER_H

#include "cocos2d.h"
#include "RT_COCOS\CCMenuItemSpriteExtra.h"

class UILayer : public cocos2d::CCLayerColor {
public:
	static UILayer* create();
	bool init();

	void onPause(cocos2d::CCObject* sender);	
protected:
	CCMenuItemSpriteExtra* m_pauseBtn;
};

#endif