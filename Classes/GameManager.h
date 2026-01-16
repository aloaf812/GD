#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include "SimplePlayer.h"
#include <stdio.h>
// layers
#include "PlayLayer.h"
#include "LevelSelectLayer.h"

#define PLAY_LAYER GameManager::sharedState()->getPlayLayer()

// thanks geode
enum class UnlockType {
    Cube = 1,
    Col1 = 2,
    Col2 = 3,
    Ship = 4,
    Ball = 5,
    Bird = 6
};

// i'll figure these values out when i can
enum class LastGameScene {
    unk0 = 0,
    unk1 = 1,
	EditorLevels = 2,
    unk3 = 3,
    unk4 = 4,
    unk5 = 5,
    unk6 = 6,
    unk7 = 7,
    unk8 = 8,
    LevelSelect = 9
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
    void toggleFX();
    void toggleMusic();
    int colorForPos(int color);
    std::string colorKey(int param_1, bool param_2);
    virtual void dataLoaded(DS_Dictionary* param_1);
    /**
    @param col The number of the player color.
    @returns an RGB color in ccColor3B form corresponding to the player color #.
    */
    static cocos2d::ccColor3B colorForIdx(int col);
    // clean CC_PROPERTY lines
	CC_PROPERTY(bool, m_performanceMode, PerformanceMode); // 0x56
    CC_PROPERTY(bool, m_clickedGarage, ClickedGarage); // 0x59
    CC_PROPERTY(bool, m_clickedEditor, ClickedEditor); // 0x5a
    // icons
    CC_PROPERTY(int, m_playerColor, PlayerColor); // 0x158
    CC_PROPERTY(int, m_playerColor2, PlayerColor2); // 0x15c
    CC_PROPERTY(int, m_playerFrame, PlayerFrame); // 0x148
    CC_PROPERTY(int, m_playerShip, PlayerShip); // 0x14c
    CC_PROPERTY(int, m_playerBall, PlayerBall); // 0x150
    CC_PROPERTY(int, m_playerBird, PlayerBird); // 0x154
    CC_PROPERTY(int, m_playerStreak, PlayerStreak); // 0x160
    CC_PROPERTY(IconType, m_playerIconType, PlayerIconType); // 0x164
    // layers
    CC_PROPERTY(PlayLayer*, m_playLayer, PlayLayer); // 0x114
    CC_PROPERTY(LevelSelectLayer*, m_levelSelectLayer, LevelSelectLayer); // 0x118
    CC_PROPERTY(bool, m_mainMenuActive, MainMenuActive); // 0x11c
    // get functions
    bool getEditMode();
    bool getGameCenterEnabled();
    // set functions
    void setFirstSetup(bool firstSetup);
    void setLastScene(LastGameScene scene);
    void setEditMode(bool edit);
    void setWasHigh(bool wasHigh);
protected:
    // made before i started with the variables
    bool m_clickedName;
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
