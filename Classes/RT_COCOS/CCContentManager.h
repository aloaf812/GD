#ifndef __GeometryDash__CCContentManager__
#define __GeometryDash__CCContentManager__

#include "cocos2d.h"

class CCContentManager : public cocos2d::CCObject {
    cocos2d::CCDictionary* m_pDicts = nullptr;
public:
    static CCContentManager* sharedManager();
    CCContentManager();
    bool init();
    cocos2d::CCDictionary* addDict(char const* filePath, bool unk);
};

#endif /* defined(__GeometryDash__CCContentManager__) */
