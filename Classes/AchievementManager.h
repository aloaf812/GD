#ifndef _ACHIEVEMENT_MANAGER_H_
#define _ACHIEVEMENT_MANAGER_H_

#include "cocos2d.h"

class AchievementManager : public cocos2d::CCNode {
public:
	AchievementManager();
    static AchievementManager* sharedState();
	virtual bool init();
	void notifyAchievementWithID(char const* achID);
	void reportAchievementWithID(char const* achID, int percentage, bool param_3);
	bool isAchievementEarned(char const* achID);
	bool areAchievementsEarned(cocos2d::CCArray* achSet);
	int percentForAchievement(char const* achID);

	bool m_dontNotifyAch;
	cocos2d::CCDictionary* m_achDict;
	cocos2d::CCDictionary* m_reportedAchDict;
};


#endif