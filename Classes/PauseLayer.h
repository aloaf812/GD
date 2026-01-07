#ifndef __GeometryDash__PauseLayer__
#define __GeometryDash__PauseLayer__

#include "cocos2d.h"

class PauseLayer : public cocos2d::CCLayer {
public:
    static PauseLayer* create();
    // virtual bool init();
    void onAutoCheckpoints(cocos2d::CCObject* sender);
    void onAutoRetry(cocos2d::CCObject* sender);
    void onEdit(cocos2d::CCObject* sender);
    void onFX(cocos2d::CCObject* sender);
    void onHelp(cocos2d::CCObject* sender);
    void onMusic(cocos2d::CCObject* sender);
    void onNormalMode(cocos2d::CCObject* sender);
    void onPracticeMode(cocos2d::CCObject* sender);
    void onQuit(cocos2d::CCObject* sender);
    void onRecordReplays(cocos2d::CCObject* sender);
    void onRestart(cocos2d::CCObject* sender);
    void onResume(cocos2d::CCObject* sender);
};

#endif /* defined(__GeometryDash__PauseLayer__) */
