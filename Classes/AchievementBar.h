#ifndef _ACHIEVEMENT_BAR_H_
#define _ACHIEVEMENT_BAR_H_
#include "cocos2d.h"

class AchievementBar : public cocos2d::CCNodeRGBA {
public:
	AchievementBar();
	static AchievementBar* create(char const* title, char const* description, char const* icon);
	virtual bool init(char const* title, char const* description, char const* icon);
	void show();

	CC_PROPERTY(CCNode*, m_targetScene, TargetScene);
};

#endif