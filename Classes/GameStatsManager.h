#ifndef __GeometryDash__GameStatsManager__
#define __GeometryDash__GameStatsManager__

#include "cocos2d.h"

class GameStatsManager : cocos2d::CCNode {
public:
    static GameStatsManager* sharedState();
    virtual bool init();

	void dataLoaded(DS_Dictionary* dict);
	void encodeDataTo(DS_Dictionary* dict);
	 
    int getStat(char const* stat);
protected:
	cocos2d::CCDictionary* m_valueDict; // 0xe8
	cocos2d::CCDictionary* m_completedLevels; // 0xec
	cocos2d::CCDictionary* m_liteAchievementsDict; // 0xf0
};

#endif /* defined(__GeometryDash__GameStatsManager__) */
