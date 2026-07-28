#ifndef _OPTIONS_LAYER_H_
#define _OPTIONS_LAYER_H_

#include "cocos2d.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "GJDropDownLayer.h"

class OptionsLayer : public GJDropDownLayer {
public:
    static OptionsLayer* create();
	void createToggleButton(std::string text, cocos2d::SEL_MenuHandler callback, bool toggled, cocos2d::CCMenu* menu, cocos2d::CCPoint position);
	void customSetup();
	void toggleGP();

	void onGC(CCObject* sender);
	void onGPSignIn(CCObject* sender);
	void onGPSignOut(CCObject* sender);
	void onSupport(CCObject* sender);
	void onSoundtracks(CCObject* sender);
	void onHelp(CCObject* sender);
	void onRate(CCObject* sender);
	void onMusic(CCObject* sender);
	void onFX(CCObject* sender);
	void onAutoCheckpoints(CCObject* sender);
	void onAutoRetry(CCObject* sender);

	// GooglePlayManager* m_gPlayDelegate; // 0x1ac
	cocos2d::CCMenu* m_optionsMenu; // 0x1b0
	bool unk_0x1bd; // 0x1bd
	bool unk_0x1bc; // 0x1bc
	CCMenuItemSpriteExtra* m_gpSignIn; // 0x1b4
	CCMenuItemSpriteExtra* m_gpSignOut; // 0x1b8
};

#endif