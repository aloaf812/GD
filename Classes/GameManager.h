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
#define WIN_SIZE cocos2d::CCDirector::sharedDirector()->getWinSize()
#define SCREEN_SCALE_F_W CCDirector::sharedDirector()->getScreenScaleFactorW()
#define SCREEN_SCALE_F_H CCDirector::sharedDirector()->getScreenScaleFactorH()
// apparently somehow for some reason robtop sometimes doesnt define GameManager as a variable in functions so i made this macro to make code slightly more readable
#define GM GameManager::sharedState()

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

// unused boomlings class
class PremiumPopup;
class GameRateDelegate;

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
	void rateGame();
    void toggleFX();
    void toggleMusic();
	void resetMusic();
    int colorForPos(int color);
    std::string colorKey(int param_1, bool param_2);
	void returnToLastScene(GJGameLevel* level);

	virtual void setup();
	virtual void encodeDataTo(DS_Dictionary* dict);
	virtual void dataLoaded(DS_Dictionary* dict);
    virtual void firstLoad();
    /**
    @param col The number of the player color.
    @returns an RGB color in ccColor3B form corresponding to the player color #.
    */
    cocos2d::ccColor3B colorForIdx(int col);

	bool unk_0xee; // 0xee
	bool unk_0xef; // 0xef
    
	cocos2d::CCDictionary* m_scoreKeeper; // 0xf0
	cocos2d::CCDictionary* m_valueKeeper; // 0xf4
	
	float unk_0xf8; // 0xf8
	int unk_0x100; // 0x100
	std::string unk_0x104; // 0x104

	CC_SYNTHESIZE(bool, m_didSyncAchievements, DidSyncAchievements); // 0x110
	CC_SYNTHESIZE(PlayLayer*, m_playLayer, PlayLayer); // 0x114
	CC_SYNTHESIZE(LevelSelectLayer*, m_levelSelectLayer, LevelSelectLayer); // 0x118
	CC_SYNTHESIZE(bool, m_mainMenuActive, MainMenuActive); // 0x11c
	CC_SYNTHESIZE(PremiumPopup*, m_premiumPopup, PremiumPopup); // 0x120
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
	CC_SYNTHESIZE(bool, m_wasHigh, WasHigh); // 0x13a
	CC_SYNTHESIZE(bool, m_editMode, EditMode); // 0x13b
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
	CC_SYNTHESIZE(bool, m_showedRateDiffDialog, ShowedRateDiffDialog); // 0x176
	CC_SYNTHESIZE(bool, m_showedRateStarDialog, ShowedRateStarDialog); // 0x177
	CC_SYNTHESIZE(bool, m_showedLowDetailDialog, ShowedLowDetailDialog); // 0x178
    
	CC_SYNTHESIZE(GameRateDelegate*, m_rateDelegate, RateDelegate); // 0x17c
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_storedColor, StoredColor); // 0x180
	CC_SYNTHESIZE(int, m_lastLevelID, LastLevelID); // 0x184
	CC_SYNTHESIZE_READONLY(int, m_loadedBGIdx, LoadedBGIdx); // 0x188
	CC_SYNTHESIZE_READONLY(int, m_loadedGIdx, LoadedGIdx); // 0x18c
	CC_SYNTHESIZE(int, m_totalAttempts, TotalAttempts); // 0x190
	CC_SYNTHESIZE_READONLY(bool, m_fullUnlocked, FullUnlocked); // 0x194
protected:
    bool m_enableTutorial;
    bool m_hasRatedGame;
};

#endif /* defined(__GeometryDash__GameManager__) */
