#ifndef __GeometryDash__LocalLevelManager__
#define __GeometryDash__LocalLevelManager__

#include "cocos2d.h"
#include "GManager.h"
#include <stdio.h>

class LocalLevelManager : public GManager {
public:
    LocalLevelManager();
    static LocalLevelManager* sharedState();
    virtual bool init();
    void setup();
    std::string getMainLevelString(int level);

    cocos2d::CCDictionary* m_mainLevels; // 0xf0
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_localLevels, LocalLevels); // 0xf4
};

#endif /* defined(__GeometryDash__LocalLevelManager__) */
