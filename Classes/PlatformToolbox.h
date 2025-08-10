#ifndef __GeometryDash__PlatformToolbox__
#define __GeometryDash__PlatformToolbox__

#include "cocos2d.h"

/**
@brief Manages platform-specific functionality 
*/
class PlatformToolbox {
public:
    static void gameDidSave();
    static uint shouldResumeSound();
    static bool isHD();
    static bool isLocalPlayerAuthenticated();
    static void activateGameCenter();
    static bool isSignedIntoGooglePlay();
    static bool isNetworkAvailable();
    static void logEvent(char const* event);
    // android only // void reportLoadingFinished();
};

#endif /* defined(__GeometryDash__PlatformToolbox__) */
