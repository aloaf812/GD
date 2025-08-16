#ifndef __GeometryDash__MenuLayer__
#define __GeometryDash__MenuLayer__

#include "cocos2d.h"
/**
@brief The background layer of the main menu with the scrolling BG/ground and the jumping icons
*/
class MenuLayer: public cocos2d::CCLayer {
public:
    static cocos2d::CCScene* scene();
    static MenuLayer* node();
    virtual bool init();
    void onPlay(CCObject* sender);
    void onGarage(CCObject* sender);
    void onCreator(CCObject* sender);
    void onOptions(CCObject* sender);
    void onAchievements(CCObject* sender);
    void onStats(CCObject* sender);
    void onRobTop(CCObject* sender);
    void onFacebook(CCObject* sender);
    void onTwitter(CCObject* sender);
    /**
     @brief Runs when the "More Games" button is pressed in the main menu
     */
    void onMoreGames(cocos2d::CCObject* sender);
};

#endif