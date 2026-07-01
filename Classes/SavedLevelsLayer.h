#ifndef __SAVED_LEVELS_LAYER_H__
#define __SAVED_LEVELS_LAYER_H__

#include "cocos2d.h"

class SavedLevelsLayer : public cocos2d::CCLayer {
public:
	CREATE_FUNC(SavedLevelsLayer);
	bool init();
	void onBack(cocos2d::CCObject* sender);
	void setupLevelBrowser();
};

#endif