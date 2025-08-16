#ifndef __GeometryDash__MenuGameLayer__
#define __GeometryDash__MenuGameLayer__

#include "cocos2d.h"

class MenuGameLayer: public cocos2d::CCLayer {
public:
    virtual bool init();
    cocos2d::ccColor3B getBGColor(int p0);
};

#endif /* defined(__GeometryDash__MenuGameLayer__) */
