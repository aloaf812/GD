#ifndef _RETRY_LEVEL_LAYER_H_
#define _RETRY_LEVEL_LAYER_H_

#include "cocos2d.h"
#include "GJDropDownLayer.h"

class RetryLevelLayer : public GJDropDownLayer {
public:
	static RetryLevelLayer* create();
	void customSetup();
	void setupLastProgress();
	void enterAnimFinished();
	void showLayer(bool instantShow);
	void keyBackClicked();

	void onMenu(cocos2d::CCObject* sender);
	void onReplay(cocos2d::CCObject* sender);
	void onEveryplay(cocos2d::CCObject* sender);

	cocos2d::CCMenu* m_buttonMenu; // 0x1a8
};

#endif