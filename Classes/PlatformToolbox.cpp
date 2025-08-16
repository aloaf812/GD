#include "PlatformToolbox.h"
USING_NS_CC;

void PlatformToolbox::gameDidSave(){
    return;
}

bool PlatformToolbox::shouldResumeSound(){
    return true;
}

bool PlatformToolbox::isHD(){
    return false;
}

bool PlatformToolbox::isLocalPlayerAuthenticated(){
    return false;
}

bool PlatformToolbox::isSignedIntoGooglePlay(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    if (! JniHelper::getStaticMethodInfo(methodInfo, "com/customRobTop/BaseRobTopActivity", "gameServicesIsSignedIn", "()Z")) {
        return true;
        }
    #else
        return false;
    #endif
}

bool PlatformToolbox::isNetworkAvailable(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        return false;
    #else
        return false;
    #endif
}

void PlatformToolbox::activateGameCenter(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // TODO: add Objective-C code
        return;
    #else
        return;
    #endif
}

void PlatformToolbox::logEvent(char const* event) {
    CCLOG(event);
}