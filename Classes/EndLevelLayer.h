#ifndef _END_LEVEL_LAYER_H
#define _END_LEVEL_LAYER_H

#include "GJDropDownLayer.h"

class EndLevelLayer : public GJDropDownLayer {
    char const* getEndText();

	void onMenu(cocos2d::CCObject* sender);
	void onReplay(cocos2d::CCObject* sender);
	void onEveryplay(cocos2d::CCObject* sender);
};

#endif