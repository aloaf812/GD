#include "GameToolbox.h"
#include "PlatformToolbox.h"
USING_NS_CC;

bool GameToolbox::isIOS(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return true;
#else
    return false;
#endif
}

bool GameToolbox::doWeHaveInternet(){
    return true;
}