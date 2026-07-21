#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"
#include "RT_COCOS/CCBlockLayer.h"

class PauseLayer : public CCBlockLayer {
public:
	CREATE_FUNC(PauseLayer);
    void customSetup();

	void createToggleButton(std::string text, cocos2d::SEL_MenuHandler callback, bool toggled, cocos2d::CCMenu* menu, cocos2d::CCPoint position);
	void setupProgressBars();

    void onAutoCheckpoints(cocos2d::CCObject* sender);
    void onAutoRetry(cocos2d::CCObject* sender);
    void onEdit(cocos2d::CCObject* sender);
    void onFX(cocos2d::CCObject* sender);
    void onHelp(cocos2d::CCObject* sender);
    void onMusic(cocos2d::CCObject* sender);
    void onNormalMode(cocos2d::CCObject* sender);
    void onPracticeMode(cocos2d::CCObject* sender);
	void onProgressBar(cocos2d::CCObject* sender);
    void onQuit(cocos2d::CCObject* sender);
    void onRecordReplays(cocos2d::CCObject* sender);
    void onRestart(cocos2d::CCObject* sender);
    void onResume(cocos2d::CCObject* sender);
};

#endif /* defined(__PAUSE_LAYER_H__) */
