#ifndef _PLAY_LAYER_H
#define _PLAY_LAYER_H

#include "cocos2d.h"
#include "GJBaseGameLayer.h"
#include "GJGameLevel.h"

class PlayLayer : public GJBaseGameLayer {
public:
    PlayLayer();
    static cocos2d::CCScene* scene(GJGameLevel* level);
    static PlayLayer* create(GJGameLevel* level);
    bool init(GJGameLevel* level);
    void onQuit();

    CC_PROPERTY(bool, m_playbackMode, PlaybackMode); // 0x229
    CC_PROPERTY_READONLY(int, m_cameraPortal, CameraPortal); // 0x234
    CC_PROPERTY_READONLY(bool, m_isFlipped, IsFlipped); // 0x238
    CC_PROPERTY_READONLY(float, m_flipValue, FlipValue); // 0x23c
    CC_PROPERTY_READONLY(int, m_GEM, GEM); // 0x240
    // CC_PROPERTY_READONLY(UILayer*, m_uiLayer, UILayer); // 0x244
    // CC_PROPERTY_READONLY(PlayerObject*, m_player, Player); // 0x248
    CC_PROPERTY_READONLY(GJGameLevel*, m_level, Level); // 0x24c
    // 0x250
    // 0x254
    CC_PROPERTY_READONLY(bool, m_testMode, TestMode); // 0x258
    CC_PROPERTY_READONLY(bool, m_practiceMode, PracticeMode); // 0x259
    CC_PROPERTY(bool, m_isResetting, IsResetting); // 0x25a
    CC_PROPERTY_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNode, BatchNode); // 0x25c
    CC_PROPERTY_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNodeBottom, BatchNodeBottom); // 0x260
    CC_PROPERTY_READONLY(cocos2d::CCLayer*, m_gameLayer, GameLayer); // 0x264
    CC_PROPERTY_READONLY(cocos2d::CCArray*, m_bigActionContainer, BigActionContainer); // 0x268
    CC_PROPERTY_READONLY(bool, m_cleanReset, CleanReset); // 0x270
    // 0x274
    // 0x278
    CC_PROPERTY_READONLY(int, m_attempts, Attempts); // 0x27c
    CC_PROPERTY_READONLY(int, m_jumps, Jumps); // 0x280
    CC_PROPERTY_READONLY(bool, m_didJump, DidJump); // 0x284
    CC_PROPERTY_READONLY(float, m_clkTimer, ClkTimer); // 0x288
    CC_PROPERTY(bool, m_showingEndLayer, ShowingEndLayer); // 0x28c
    CC_PROPERTY(bool, m_endTriggered, EndTriggered); // 0x28d
    CC_PROPERTY(bool, m_resetQueued, ResetQueued); // 0x28e
    CC_PROPERTY(int, m_lastRunPercent, LastRunPercent); // 0x290
    CC_PROPERTY_READONLY(bool, m_didAwardStars, DidAwardStars); // 0x294
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeBGColorAction, ActiveBGColorAction); // 0x298
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeGColorAction, ActiveGColorAction); // 0x29c
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeLineColorAction, ActiveLineColorAction); // 0x2a0
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeObjColorAction, ActiveObjColorAction); // 0x2a4
    CC_PROPERTY_READONLY(cocos2d::CCAction*, m_activeTintObjColorAction, ActiveTintObjColorAction); // 0x2a8
    CC_PROPERTY(bool, m_shouldRestartAfterStopped, ShouldRestartAfterStopped); // 0x2ac
};

#endif
