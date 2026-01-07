#ifndef __GeometryDash__ObjectToolbox__
#define __GeometryDash__ObjectToolbox__

#include "cocos2d.h"

class ObjectToolbox : public cocos2d::CCNode {
public:
    static cocos2d::CCDictionary* stringSetupToDict(std::string str);
};

#endif /* defined(__GeometryDash__ObjectToolbox__) */
