#include "MenuLayer.h"
#include "PlatformToolbox.h"
#include "GameManager.h"
USING_NS_CC;

CCScene* MenuLayer::scene(){

}

void MenuLayer::onMoreGames(CCObject* sender) {
    PlatformToolbox::logEvent("MoreGames");
    GameManager::sharedState()->reportAchievementWithID("geometry.ach.moreGames", 100, false);
    return;
}

/* armeabi: 0x8b8f0
bool MenuLayer::init(...) {
    if (!CCLayer::init())
        return false;

    // add code here

    return true;
}
*/