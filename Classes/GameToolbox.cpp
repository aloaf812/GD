#include "GameToolbox.h"

bool isIOS(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return true;
#else
    return false;
#endif
}