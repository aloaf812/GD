#include "GameToolbox.h"

bool isIOS(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLOG("ios ios ios ios");
    return 1;
#else
    CCLOG("android android android android android android android android");
    return 0;
#endif
}