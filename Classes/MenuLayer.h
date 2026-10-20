#ifndef __GeometryDash__MenuLayer__
#define __GeometryDash__MenuLayer__

#include "cocos2d.h"
#include "FLAlertLayer.h"
#include "GooglePlayManager.h"

class MenuLayer: public cocos2d::CCLayer {
public:
    static cocos2d::CCScene* scene();
	NODE_FUNC(MenuLayer);
    bool init();

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
	void onEveryplay(cocos2d::CCObject* sender);

    void showGCQuestion();
    void willClose();
    /**
     @brief Runs when the "More Games" button is pressed in the main menu
     */
    void onMoreGames(cocos2d::CCObject* sender);
	void endGame();
	void syncPlatformAchievements(float dt);
	void tryShowAd(float dt);
	void keyBackClicked();
	void showPirateMessage();
	virtual void googlePlaySignedIn();
	virtual void FLAlert_Clicked(FLAlertLayer* layer, bool button2Clicked);

	FLAlertLayerProtocol* unk_0x10c; // 0x10c
	GooglePlayDelegate* m_gpDelegate; // 0x110
	cocos2d::CCSprite* m_platformSpr; // 0x114
};

#endif