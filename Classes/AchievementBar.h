#ifndef _ACHIEVEMENT_BAR_H_
#define _ACHIEVEMENT_BAR_H_
#include "cocos2d.h"

class AchievementBar : public cocos2d::CCNodeRGBA {
public:
	AchievementBar();
	static AchievementBar* create(char const* title, char const* description, char const* icon);
	virtual bool init(char const* title, char const* description, char const* icon);
	void show();


	cocos2d::CCLayerColor* m_layerColor; // 0xe8
	float m_screenOffset; // 0xec
	CC_SYNTHESIZE(CCNode*, m_targetScene, TargetScene); // 0xf0
};

#endif