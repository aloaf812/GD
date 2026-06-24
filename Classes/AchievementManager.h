#ifndef _ACHIEVEMENT_MANAGER_H_
#define _ACHIEVEMENT_MANAGER_H_

#include "cocos2d.h"

class AchievementManager : public cocos2d::CCNode {
public:
	AchievementManager();
	virtual ~AchievementManager();
	static AchievementManager* sharedState();
	virtual bool init();

	void notifyAchievementWithID(char const* achID);
	void reportAchievementWithID(char const* achID, int percentage, bool param_3);
	bool isAchievementEarned(char const* achID);
	bool areAchievementsEarned(cocos2d::CCArray* achSet);
	int percentForAchievement(char const* achID);

	void setup();
	void checkAchFromUnlock(char const* achID);
	int percentageForCount(int count, int total);
	cocos2d::CCDictionary* getAllAchievements();
	cocos2d::CCDictionary* getAchievementsWithID(char const* achID);
	void resetAchievement(char const* achID);
	void resetAchievements();
	void reportPlatformAchievementWithID(char const* achID, int percentage);

	cocos2d::CCDictionary* m_allAchievements;
	CC_SYNTHESIZE(cocos2d::CCDictionary*, m_reportedAchievements, ReportedAchievements);
	bool m_dontNotifyAch;
};

#endif