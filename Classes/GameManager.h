#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include "SimplePlayer.h"
#include <stdio.h>

// thanks geode
enum class UnlockType {
    Cube = 1,
    Col1 = 2,
    Col2 = 3,
    Ship = 4,
    Ball = 5,
    Bird = 6
};

enum class LastGameScene {
    Menuaaayer = 8,
    MenuPlayer = 0,
    MenuGamePlae = 20
};

class GameManager: public GManager {
public:
    GameManager();
    // ~GameManager();
    static GameManager* sharedState();
    /**
    @returns A background texture file depending on the value in the id field.
    */
    char const* getBGTexture(int bgID);
    /**
    @returns A ground texture file depending on the value in the id field.
    */
    char const* getGTexture(int gID);
    virtual bool init();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    /**
    @param ach_ID The ID of the achievment of the achievement being reported (e.g. geometry.ach.moreGames)
    @param percentage The completion percentage of the achievement
    @param param_3 A bool parameter 
    */
    void reportAchievementWithID(char const* ach_ID, int percentage, bool param_3);
    void completedAchievement(char const* ach_ID);
    /**
    @param fileName The file of the music which will be faded in.
    */
    void fadeInMusic(char const* fileName);
    // char const* iconKey(int id, IconType type);
    void loadBackground(int param_1);
    void loadGround(int gID);
    void syncPlatformAchievements();
    void followTwitter();
    void likeFacebook();
    void firstLoad();
    void rateGame();
    int colorForPos(int color);
    std::string colorKey(int param_1, bool param_2);
    virtual void dataLoaded(DS_Dictionary* param_1);
    // get functions
    bool getClickedGarage();
    bool getClickedEditor();
    bool getEditMode();
    bool getGameCenterEnabled();
    // set functions
    void setMainMenuActive(bool active);
    void setClickedGarage(bool clickedGarage);
    void setClickedEditor(bool clickedEditor);
    void setFirstSetup(bool firstSetup);
    void setLastScene(LastGameScene scene);
    void setEditMode(bool edit);
    void setWasHigh(bool wasHigh);
protected:
    // made before i started with the variables
    bool m_clickedGarage;
    bool m_clickedEditor;
    bool m_clickedName;
    // dictionaries
    cocos2d::CCDictionary* m_valueKeeper;
    bool m_mainMenuActive;
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
    bool m_showedPirate;
    bool m_hasRatedGame;
    bool m_clickedPractice;
    bool m_showedEditorGuide;
    int m_loadedBgID;
    int m_loadedGroundID;
    int m_lastLevelID;
    int m_totalAttempts;
    int m_playerUserID;
    LastGameScene m_lastScene;
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
    bool m_editMode;
    bool m_wasHigh;
};

#endif /* defined(__GeometryDash__GameManager__) */
