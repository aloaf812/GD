//
//  GameToolbox.cpp
//  GeometryDash
//
//  Created by bryan on 7/27/25.
//
//

#include "GameToolbox.h"

bool isIOS(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLOG("you're on an inferior platform");
    return 1;
#else
    CCLOG("android android android android android android android android");
    return 0;
#endif
}