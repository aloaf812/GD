#ifndef __GeometryDash__GameToolbox__
#define __GeometryDash__GameToolbox__

#include "cocos2d.h"

class GameToolbox: public cocos2d::CCLayer {
public:
    
    static bool isIOS();
    static bool doWeHaveInternet();
    // do the rest later
};

#endif