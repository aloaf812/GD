#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include "SimplePlayer.h"
#include <stdio.h>

// thanks geode
enum class UnlockType {
    Cube = 0x1,
    Col1 = 0x2,
    Col2 = 0x3,
    Ship = 0x4,
    Ball = 0x5,
    Bird = 0x6
};

class GameManager: public GManager {
public:
    GameManager();
    ~GameManager();
    static GameManager* sharedState();
    /**
    @returns A texture file depending on the value in the id field.
    */
    char const* getBGTexture(int id);
    virtual bool init();
    /**
    @param ach_ID The ID of the achievment of the achievement being reported (e.g. geometry.ach.moreGames)
    @param percentage The completion percentage of the achievement
    @param param_3 A bool parameter 
    */
    void reportAchievementWithID(char const* ach_ID, int percentage, bool param_3);
    /**
    @param fileName The file of the music which will be faded in.
    */
    void fadeInMusic(char const* fileName);
    // char const* iconKey(int id, IconType type);
    void loadBackground(int param_1);
    void syncPlatformAchievements();
    void followTwitter();
    void likeFacebook();
    bool m_clickedGarage;
    bool m_clickedEditor;
    bool m_clickedName;
    void firstLoad();
    void rateGame();
    int colorForPos(int color);
    std::string colorKey(int param_1, UnlockType param_2);
    virtual void dataLoaded(DS_Dictionary* param_1);
protected:
    // dictionaries
    cocos2d::CCDictionary* m_valueKeeper;
    bool m_gameCenterEnabled;
    bool m_firstSetup;
    bool m_showedFirstTutorial;
    bool m_musicEnabled;
    bool m_fxEnabled;
    bool m_autoCheckpoints;
    bool m_showSongMarkers;
    bool m_showBPMMarkers;
    bool m_autoRetry;
    bool m_showProgressBar;
    bool m_commentSortRecent;
    bool m_performanceMode;
    bool m_enableTutorial;
    bool m_didSyncAchievements;
    int m_loadedBgID;
    // icons
    int m_playerColor;
    int m_playerColor2;
    int m_playerFrame;
    int m_playerShip;
    int m_playerBall;
    int m_playerBird;
    int m_playerStreak;
    IconType m_playerIconType;
    // unknown values
    bool offset_0x5;
    bool offset_0xf;
    // social media
    bool m_clickedFacebook;
    bool m_clickedTwitter;
    // i can't figure this out: bool offset_0x6;
    bool m_showedRateDiffDialog;
    bool m_showedRateStarDialog;
    bool m_showedLowDetailDialog;
    bool m_recordGameplay;
    bool m_playerScoreValid;
    std::string m_playerName;
    std::string m_playerUDID;
};

#endif /* defined(__GeometryDash__GameManager__) */
