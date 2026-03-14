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
// omnimenu has some of these values
enum class LastGameScene {
	unk0 = 0,
	SearchScene = 1,
	EditorLevels = 2,
	unk3 = 3,
	unk4 = 4,
	unk5 = 5,
	CreatorsScores = 6,
	unk7 = 7,
	unk8 = 8,
	LevelSelect = 9,
	PreviousSearch = 10
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
    void applicationDidEnterBackground();
    void applicationWillEnterForeground();
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
	void resetMusic();
    int colorForPos(int color);
    std::string colorKey(int param_1, bool param_2);

	virtual void setup();
    virtual void dataLoaded(DS_Dictionary* param_1);
    /**
    @param col The number of the player color.
    @returns an RGB color in ccColor3B form corresponding to the player color #.
    */
    static cocos2d::ccColor3B colorForIdx(int col);

	CC_SYNTHESIZE(PlayLayer*, m_playLayer, PlayLayer); // 0x114
	CC_SYNTHESIZE(LevelSelectLayer*, m_levelSelectLayer, LevelSelectLayer); // 0x118
	CC_SYNTHESIZE(bool, m_mainMenuActive, MainMenuActive); // 0x11c
	// CC_SYNTHESIZE(PremiumPopup*, m_premiumPopup, PremiumPopup); // 0x120
	CC_SYNTHESIZE(bool, m_gameCenterEnabled, GameCenterEnabled); // 0x124
	CC_SYNTHESIZE(bool, m_firstSetup, FirstSetup); // 0x125
	CC_SYNTHESIZE(bool, m_showedFirstTutorial, ShowedFirstTutorial); // 0x126
	CC_SYNTHESIZE(std::string, m_playerUDID, PlayerUDID); // 0x128
	CC_SYNTHESIZE(std::string, m_playerName, PlayerName); // 0x12c

	CC_SYNTHESIZE(int, m_playerUserID, PlayerUserID); // 0x130
	CC_SYNTHESIZE(bool, m_playerScoreValid, PlayerScoreValid); // 0x134
	CC_SYNTHESIZE_READONLY(bool, m_musicEnabled, MusicEnabled); // 0x135
	CC_SYNTHESIZE_READONLY(bool, m_fxEnabled, FxEnabled); // 0x136
	CC_SYNTHESIZE(bool, m_didRateGame, DidRateGame); // 0x137
	CC_SYNTHESIZE(bool, m_didLikeFacebook, DidLikeFacebook); // 0x138
	CC_SYNTHESIZE(bool, m_didFollowTwitter, DidFollowTwitter); // 0x139
	CC_SYNTHESIZE(bool, m_editMode, EditMode); // 0x13b
	CC_SYNTHESIZE(bool, m_wasHigh, WasHigh); // 0x13a
	CC_SYNTHESIZE(LastGameScene, m_lastScene, LastScene); // 0x13c
	CC_SYNTHESIZE(LastGameScene, m_lastScene2, LastScene2); // 0x140
	CC_SYNTHESIZE(bool, m_returnToSearch, ReturnToSearch); // 0x144

    // icons
	CC_SYNTHESIZE(int, m_playerFrame, PlayerFrame); // 0x148
	CC_SYNTHESIZE(int, m_playerShip, PlayerShip); // 0x14c
    CC_SYNTHESIZE(int, m_playerBall, PlayerBall); // 0x150
	CC_SYNTHESIZE(int, m_playerBird, PlayerBird); // 0x154
	CC_SYNTHESIZE(int, m_playerColor, PlayerColor); // 0x158
	CC_SYNTHESIZE(int, m_playerColor2, PlayerColor2); // 0x15c
	CC_SYNTHESIZE(int, m_playerStreak, PlayerStreak); // 0x160
	CC_SYNTHESIZE(IconType, m_playerIconType, PlayerIconType); // 0x164

	// the great boolean wall
	CC_SYNTHESIZE(bool, m_autoCheckpoints, AutoCheckpoints); // 0x168
	CC_SYNTHESIZE(bool, m_showSongMarkers, ShowSongMarkers); // 0x169
	CC_SYNTHESIZE(bool, m_showBPMMarkers, ShowBPMMarkers); // 0x16a
	CC_SYNTHESIZE(bool, m_recordGameplay, RecordGameplay); // 0x16b
	CC_SYNTHESIZE(bool, m_autoRetryLevel, AutoRetryLevel); // 0x16c
	CC_SYNTHESIZE(bool, m_showProgressBar, ShowProgressBar) // 0x16d
	CC_SYNTHESIZE(bool, m_performanceMode, PerformanceMode); // 0x16e
	CC_SYNTHESIZE(bool, m_commentSortRecent, CommentSortRecent); // 0x16f
	CC_SYNTHESIZE(bool, m_showedPirate, ShowedPirate); // 0x170
	CC_SYNTHESIZE(bool, m_clickedGarage, ClickedGarage); // 0x171
	CC_SYNTHESIZE(bool, m_clickedEditor, ClickedEditor); // 0x172
	CC_SYNTHESIZE(bool, m_clickedName, ClickedName); // 0x173
	CC_SYNTHESIZE(bool, m_clickedPractice, ClickedPractice); // 0x174
	CC_SYNTHESIZE(bool, m_showedEditorGuide, ShowedEditorGuide); // 0x175
    
	CC_SYNTHESIZE_READONLY(int, m_loadedBGIdx, LoadedBGIdx); // 0x188
	CC_SYNTHESIZE_READONLY(int, m_loadedGIdx, LoadedGIdx); // 0x18c
	CC_SYNTHESIZE(int, m_totalAttempts, TotalAttempts); // 0x190
protected:
    // dictionaries
    cocos2d::CCDictionary* m_valueKeeper;
    bool m_enableTutorial;
    bool m_didSyncAchievements;
    bool m_hasRatedGame;
    int m_lastLevelID;
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
};

#endif /* defined(__GeometryDash__GameManager__) */
