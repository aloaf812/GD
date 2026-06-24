#ifndef _ACHIEVEMENT_NOTIFIER_H_
#define _ACHIEVEMENT_NOTIFIER_H_

#include "cocos2d.h"
#include "AchievementBar.h"

class AchievementNotifier : public cocos2d::CCNode {
public:
	AchievementNotifier();
	virtual ~AchievementNotifier();
	static AchievementNotifier* sharedState();
	virtual bool init();

	void notifyAchievement(char const* title, char const* description, char const* icon);
	void showNextAchievement();
	void achievementDisplayFinished();
	void willSwitchToScene(cocos2d::CCScene* scene);

protected:
	cocos2d::CCArray* m_achArray;
	AchievementBar* m_currentAch;
};

#endif