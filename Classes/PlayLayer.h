// MASSIVE SHOUT OUT TO ANTIMATTER FOR WRITING ALMOST ALL OF THE CC_PROPERTY/CC_SYNTHESIZE DEFINITIONS!!!!!!!!!!

#ifndef _PLAY_LAYER_H
#define _PLAY_LAYER_H

#include "cocos2d.h"
#include "GJGameLevel.h"
#include "LevelSettingsObject.h"
#include "PlayerObject.h"
#include "GJGroundLayer.h"
#include "UILayer.h"
#include "ColorAction.h"
#include "EndPortalObject.h"
//#include "GameObject.h"

enum class EnterEffect {
	unk1 = 1
};

class PlayLayer : public cocos2d::CCLayer {
public:
    PlayLayer();
    static cocos2d::CCScene* scene(GJGameLevel* level);
    static PlayLayer* create(GJGameLevel* level);
    bool init(GJGameLevel* level);

    void onQuit();
	void resume();
	void resumeAndRestart();

	void addToSection(GameObject* obj);
	void removeObjectFromSection(GameObject* obj);
    void createObjectsFromSetup(std::string setup);
    
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();

    void startGame();
	void pauseGame();
    void resetLevel();
	void fullReset();
	void delayedResetLevel();
	void showRetryLayer();

	void checkCollisions(float dt);
	int sectionForPos(cocos2d::CCPoint point);

	/*
	@param pressed If the button is pressed or not
	*/
	void recordAction(bool pressed);

	bool isFlipping();
	void destroyPlayer();

	void showHint();

    // tints
    void tintBackground(cocos2d::ccColor3B color, float duration);
    void tintGround(cocos2d::ccColor3B color, float duration);
    void tintLine(cocos2d::ccColor3B color, float duration);
    void tintObjects(cocos2d::ccColor3B color, float duration);
    void tintColorObjects(cocos2d::ccColor3B color, float duration);

	cocos2d::ccColor3B getLineColor();
	cocos2d::ccColor3B getGColor();

	// toggles
	void toggleGlitter(bool visible);
	void togglePracticeMode(bool practice);
	void toggleProgressbar();
	void toggleAudioRain(bool toggle);
    
    void registerStateObject(GameObject* obj);
    
	// updates
    void update(float dt);
    void updateAttempts();
    void updateCamera(float dt);
    void updateProgressbar();
    void updateEffectPositions();
	void updateVisibility();
	void updateLevelColors();

	void incrementJumps();

	void switchToFlyMode(GameObject* obj, bool, bool);
	void switchToRollMode(GameObject* obj, bool);

	void exitAirMode();
	void exitBirdMode();
	void exitFlyMode();
	void exitRollMode();

	// animates
	void animateInFlyGround(bool);
	void animateOutFlyGround(bool insant);
	void animateOutFlyGroundFinished();

	void animateInRollGround(bool);
	void animateOutRollGround(bool insant);
	void animateOutRollGroundFinished();

	std::string getParticleKey(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType);
	std::string getParticleKey2(std::string pKey);
	void createParticle(int objType, char const* file, int zOrder, cocos2d::tCCPositionType positionType);
	void playSpeedParticle(float timeMod);

	CheckpointObject* createCheckpoint();
	void storeCheckpoint(CheckpointObject* check);
	void markCheckpoint();

	void moveCameraToPos(cocos2d::CCPoint pos);
	void cameraMoveX(float value, float duration, float rate);
	void cameraMoveY(float value, float duration, float rate);
    
	bool hasUniqueCoin(GameObject* obj);

	float unk_0x110; // 0x110
	bool unk_0x120; // 0x120
    LevelSettingsObject* m_levelSettings; // 0x124
	EndPortalObject* m_endObject; // 0x128
	cocos2d::CCArray* m_checkpoints; // 0x12c
	cocos2d::CCArray* unk_0x130; // 0x130
	cocos2d::CCArray* unk_0x134; // 0x134
	EnterEffect m_activeEnterEffect; // 0x138
    cocos2d::CCSprite* m_background; // 0x13c
    
	cocos2d::CCSprite* unk_0x140; // 0x140
	cocos2d::CCSprite* unk_0x144; // 0x144
	cocos2d::CCSprite* unk_0x148; // 0x148
	cocos2d::CCSprite* unk_0x14c; // 0x14c

	GJGroundLayer* m_ground; // 0x150
	GJFlyGroundLayer* m_flyGroundTop; // 0x154
	GJFlyGroundLayer* m_flyGroundBottom; // 0x158
	float unk_0x15c; // 0x15c
	bool m_flyGroundActive; // 0x160
	bool m_rollGroundActive; // 0x161

	cocos2d::CCArray* m_sections; // 0x164
	cocos2d::CCArray* m_hazardsArray; // 0x168
	cocos2d::CCArray* m_activeObjects; // 0x16c
	cocos2d::CCArray* unk_0x170; // 0x170
	cocos2d::CCArray* unk_0x178; // 0x178
	cocos2d::CCArray* m_stateObjects; // 0x17c
	cocos2d::CCParticleSystemQuad* m_glitter; // 0x180
	cocos2d::CCDictionary* unk_0x184; // 0x184
	cocos2d::CCArray* m_effectObjects; // 0x188
	// AudioEffectsLayer* m_audioEffectsLayer; // 0x18c
	
	float unk_0x190; // 0x190
	float unk_0x194; // 0x194

	GJGroundLayer* m_rollGroundTop; // 0x198
	GJGroundLayer* m_rollGroundBottom; // 0x19c

	float unk_0x1a0; // 0x1a0
	float unk_0x1a4; // 0x1a4

	bool m_playerDead; // 0x1a8
	bool unk_0x1a9; // 0x1a9
	bool m_cameraMovingX; // 0x1aa
	bool m_cameraMovingY; // 0x1ab

	int unk_0x1b8; // 0x1b8
	
	float m_realLevelLength; // 0x1c0;
	cocos2d::CCLabelBMFont* m_attemptLabel; // 0x1c4 
	bool m_showingHint; // 0x1d0
	
	cocos2d::CCDictionary* m_particlesDictionary; // 0x1dc
	cocos2d::CCDictionary* unk_0x1e0; // 0x1e0

	cocos2d::CCNode* field_0x1e4;
	cocos2d::CCSprite* m_objColorRef;
	cocos2d::CCSprite* field_0x1f4;
	cocos2d::CCSprite* field_0x1e8;
	cocos2d::CCSprite* m_gColorRef; // 0x1f0

	cocos2d::CCSprite* m_progressBar; // 0x1f8
	cocos2d::CCSprite* m_progressFill; // 0x1fc
	float unk_0x200;
	float unk_0x204;

	int unk_0x20c; // 0x20c (this could be a bool)

	bool m_localLevel; // 0x210
	bool field391_0x211; // 0x211
	bool field392_0x212; // 0x212
	std::string unk_0x214; // 0x214
	double unk_0x220; // 0x220
	bool unk_0x228; // 0x228
    CC_SYNTHESIZE(bool, m_playbackMode, PlaybackMode); // 0x229
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_realPlayerPos, RealPlayerPos); // 0x22c
	CC_SYNTHESIZE_READONLY(GameObject*, m_cameraPortal, CameraPortal); // 0x234
    CC_SYNTHESIZE_READONLY(bool, m_isFlipped, IsFlipped); // 0x238
	CC_SYNTHESIZE_READONLY(float, m_flipValue, FlipValue); // 0x23c
    CC_SYNTHESIZE_READONLY(int, m_GEM, GEM); // 0x240
	CC_SYNTHESIZE_READONLY(UILayer*, m_uiLayer, UILayer); // 0x244
    CC_SYNTHESIZE_READONLY(PlayerObject*, m_player, Player); // 0x248
	CC_SYNTHESIZE_READONLY(GJGameLevel*, m_level, Level); // 0x24c
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_cameraPos, CameraPos) // 0x250
    // 0x254
	CC_SYNTHESIZE_READONLY(bool, m_testMode, TestMode); // 0x258
	CC_SYNTHESIZE_READONLY(bool, m_practiceMode, PracticeMode); // 0x259
	CC_SYNTHESIZE(bool, m_isResetting, IsResetting); // 0x25a
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNode, BatchNode); // 0x25c
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNodeBottom, BatchNodeBottom); // 0x260
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNodeAdd, BatchNodeAdd); // 0x264
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_gameLayer, GameLayer); // 0x268
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_bigActionContainer, BigActionContainer); // 0x26c
	CC_SYNTHESIZE(bool, m_cleanReset, CleanReset); // 0x270
    CC_SYNTHESIZE(cocos2d::CCPoint, m_startPos, StartPos) // 0x274
    // 0x278
	CC_SYNTHESIZE_READONLY(int, m_attempts, Attempts); // 0x27c
	CC_SYNTHESIZE_READONLY(int, m_jumps, Jumps); // 0x280
	CC_SYNTHESIZE_READONLY(bool, m_didJump, DidJump); // 0x284
	CC_SYNTHESIZE_READONLY(float, m_clkTimer, ClkTimer); // 0x288
	CC_SYNTHESIZE(bool, m_showingEndLayer, ShowingEndLayer); // 0x28c
	CC_SYNTHESIZE(bool, m_endTriggered, EndTriggered); // 0x28d
	CC_SYNTHESIZE(bool, m_resetQueued, ResetQueued); // 0x28e
    CC_SYNTHESIZE(int, m_lastRunPercent, LastRunPercent); // 0x290
	CC_SYNTHESIZE_READONLY(bool, m_didAwardStars, DidAwardStars); // 0x294
    /*CC_PROPERTY_READONLY(bool, m_tintObjectsUseBlend, TintObjectsUseBlend); // 0x294
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeBGColorAction, ActiveBGColorAction); // 0x298*/
    CC_SYNTHESIZE_READONLY(ColorAction*, m_activeGColorAction, ActiveGColorAction); // 0x29c
	virtual void setActiveGColorAction(ColorAction* action);
    /*CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeLineColorAction, ActiveLineColorAction); // 0x2a0
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeObjColorAction, ActiveObjColorAction); // 0x2a4
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeTintObjColorAction, ActiveTintObjColorAction); // 0x2a8
    CC_PROPERTY(bool, m_shouldRestartAfterStopped, ShouldRestartAfterStopped); // 0x2ac*/
	CC_SYNTHESIZE_READONLY(bool, m_tintObjectsUseBlend, TintObjectsUseBlend); // 0x2ad
};

#endif