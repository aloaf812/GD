#ifndef __GeometryDash__PlatformToolbox__
#define __GeometryDash__PlatformToolbox__

#include "cocos2d.h"

/**
@brief Manages platform-specific functionality 
*/
class PlatformToolbox {
public:
    static void gameDidSave();
    static bool shouldResumeSound();
    static bool isHD();
    static bool isLocalPlayerAuthenticated();
    static void activateGameCenter();
    static bool isNetworkAvailable();
    static void logEvent(char const* event);
    static void onNativePause();
	static void onNativeResume();
    // google play
    static bool isSignedInGooglePlay();
    static void signInGooglePlay();
    // achievements
    static void showAchievements();
    static void openAppPage();
    static void reportLoadingFinished();
	static void onToggleKeyboard();

	static std::string getUniqueUserID();
};

#endif /* defined(__GeometryDash__PlatformToolbox__) */
