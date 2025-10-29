#ifndef _ACHIEVEMENT_NOTIFIER_H_
#define _ACHIEVEMENT_NOTIFIER_H_

#include "cocos2d.h"

class AchievementNotifier : public cocos2d::CCNode {
public:
	AchievementNotifier();
	static AchievementNotifier* sharedState();
	virtual bool init();
	void notifyAchievement(char const* title, char const* description, char const* icon);
	void showNextAchievement();
	void achievementDisplayFinished();
	void willSwitchToScene(cocos2d::CCScene* scene);
};

#endif