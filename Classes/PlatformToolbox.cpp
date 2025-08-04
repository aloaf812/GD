#include "PlatformToolbox.h"

// this class is basically useless on iOS apart from the gameDidSave function

void PlatformToolbox::gameDidSave(){
    return;
}

uint PlatformToolbox::shouldResumeSound(){
    return true;
}

bool PlatformToolbox::isHD(){
    return false;
}

bool PlatformToolbox::isLocalPlayerAuthenticated(){
    return false;
}

void PlatformToolbox::activateGameCenter(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // add more functionality here
        return;
    #else
        return;
    #endif
}