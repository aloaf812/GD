#ifndef __GeometryDash__GameStatsManager__
#define __GeometryDash__GameStatsManager__

#include "cocos2d.h"

class GameStatsManager : cocos2d::CCNode {
public:
    static GameStatsManager* get();
    static GameStatsManager* sharedState();
    virtual bool init();
    int getStat(char const* stat);
protected:
    cocos2d::CCDictionary* m_unkDict1;
};

#endif /* defined(__GeometryDash__GameStatsManager__) */
