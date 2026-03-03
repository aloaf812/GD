#ifndef _UI_LAYER_H
#define _UI_LAYER_H

#include "cocos2d.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"

class UILayer : public cocos2d::CCLayerColor {
public:
	CREATE_FUNC(UILayer);
	bool init();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void keyBackClicked();

	void enableMenu();
	void disableMenu();

	void toggleCheckpointsMenu(bool visible);

	void onPause(cocos2d::CCObject* sender);	
	void onCheck(cocos2d::CCObject* sender);
	void onDeleteCheck(cocos2d::CCObject* sender);
protected:
	CCMenuItemSpriteExtra* m_pauseBtn;
	cocos2d::CCMenu* m_checkpointMenu; // 0x18c
};

#endif