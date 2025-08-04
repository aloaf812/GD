#ifndef __GeometryDash__PlatformToolbox__
#define __GeometryDash__PlatformToolbox__

#include "cocos2d.h"

class PlatformToolbox {
public:
    static void gameDidSave();
    static uint shouldResumeSound();
    static bool isHD();
    static bool isLocalPlayerAuthenticated();
    static void activateGameCenter();
    // android only // void reportLoadingFinished();
};

#endif /* defined(__GeometryDash__PlatformToolbox__) */
