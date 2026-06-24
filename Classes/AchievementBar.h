#ifndef _ACHIEVEMENT_BAR_H_
#define _ACHIEVEMENT_BAR_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class AchievementBar : public cocos2d::CCNodeRGBA {
public:
	AchievementBar();
	static AchievementBar* create(char const* title, char const* description, char const* icon);
	virtual bool init(char const* title, char const* description, char const* icon);
	void show();

	cocos2d::CCLayerColor* m_layerColor;
	float m_screenOffset;
	CC_SYNTHESIZE(cocos2d::CCNode*, m_targetScene, TargetScene);
};

#endif