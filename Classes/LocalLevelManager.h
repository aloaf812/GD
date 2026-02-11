#ifndef __GeometryDash__LocalLevelManager__
#define __GeometryDash__LocalLevelManager__

#include "cocos2d.h"
#include "GManager.h"
#include <stdio.h>

class LocalLevelManager : GManager {
public:
    LocalLevelManager();
    static LocalLevelManager* sharedState();
    virtual bool init();
    void setup();
    std::string getMainLevelString(int level);

	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_localLevels, LocalLevels); // 0x3d
protected:
    cocos2d::CCDictionary* m_mainLevels;
    std::string m_temp;
};

#endif /* defined(__GeometryDash__LocalLevelManager__) */
