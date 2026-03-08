#ifndef __GeometryDash__MenuLayer__
#define __GeometryDash__MenuLayer__

#include "cocos2d.h"
/**
@brief The background layer of the main menu with the scrolling BG/ground and the jumping icons
*/
class MenuLayer: public cocos2d::CCLayer {
public:
    static cocos2d::CCScene* scene();
	NODE_FUNC(MenuLayer);
    virtual bool init();
    void onPlay(cocos2d::CCObject* sender);
    void onGarage(cocos2d::CCObject* sender);
    void onCreator(cocos2d::CCObject* sender);
    void onOptions(cocos2d::CCObject* sender);
    void onAchievements(cocos2d::CCObject* sender);
    void onStats(cocos2d::CCObject* sender);
    void onRobTop(cocos2d::CCObject* sender);
    void onFacebook(cocos2d::CCObject* sender);
    void onTwitter(cocos2d::CCObject* sender);
    void onTrailer(cocos2d::CCObject* sender);
    void onGooglePlayGames(cocos2d::CCObject* sender);
    void onGameCenter(cocos2d::CCObject* sender);
	void onFullVersion(cocos2d::CCObject* sender);
    void showGCQuestion();
    void willClose();
    /**
     @brief Runs when the "More Games" button is pressed in the main menu
     */
    void onMoreGames(cocos2d::CCObject* sender);
};

#endif