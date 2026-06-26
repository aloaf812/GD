// decompiled by ItzZyann
// from GD 1.71 binary

#ifndef __GeometryDash__PauseLayer__
#define __GeometryDash__PauseLayer__

#include "cocos2d.h"
#include "RT_COCOS/CCBlockLayer.h"

class PauseLayer : public CCBlockLayer {
public:
	CREATE_FUNC(PauseLayer);

	virtual void customSetup();
	// virtual ~PauseLayer();

	void onAutoCheckpoints(cocos2d::CCObject* sender);
	void onAutoRetry(cocos2d::CCObject* sender);
	void onProgressBar(cocos2d::CCObject* sender);
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
	virtual void keyBackClicked();

	void tryShowBanner(float dt);
	void createToggleButton(std::string text, cocos2d::SEL_MenuHandler callback, bool toggled, cocos2d::CCMenu* menu, cocos2d::CCPoint position);
	void setupProgressBars();
};

#endif