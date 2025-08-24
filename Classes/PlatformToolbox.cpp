#include "PlatformToolbox.h"
USING_NS_CC;

// this is actually seperated in to a PlatformToolbox.m file on iOS so all of this ios is useless

void PlatformToolbox::gameDidSave(){
    return;
}

bool PlatformToolbox::shouldResumeSound(){
    return true;
}

bool PlatformToolbox::isHD(){
    // this function is broken and doesn't change the result even on retina devices
    // todo: fix
    if (CC_CONTENT_SCALE_FACTOR() == 1.0f)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool PlatformToolbox::isLocalPlayerAuthenticated(){
    return false;
}

bool PlatformToolbox::isSignedInGooglePlay(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    if (! JniHelper::getStaticMethodInfo(methodInfo,
                                         "com/customRobTop/BaseRobTopActivity",
                                         "gameServicesIsSignedIn",
                                         "()Z")) {
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

void PlatformToolbox::signInGooglePlay()
{
    
}

void PlatformToolbox::showAchievements()
{
    
}

void PlatformToolbox::openAppPage()
{
    
}

void PlatformToolbox::logEvent(char const* event)
{
    // temporary CCLOG while i figure out what this does on ios (i still don't want to code in obj-c)
    CCLOG(event);
}