#ifndef _LEVEL_SELECT_LAYER_H_
#define _LEVEL_SELECT_LAYER_H_
#include "cocos2d.h"
#include "BoomScrollLayer.h"

class LevelSelectLayer : public cocos2d::CCLayer, public BoomScrollLayerDelegate
{
public:
	LevelSelectLayer();
	static cocos2d::CCScene* scene(int page);
	static LevelSelectLayer* create(int page);
	bool init(int page);
	void update(float dt);

	void onDownload(cocos2d::CCObject* sender);
	void onBack(cocos2d::CCObject* sender);
	void onInfo(cocos2d::CCObject* sender);
	void onPrev(cocos2d::CCObject* sender);
	void onNext(cocos2d::CCObject* sender);

	virtual void keyBackClicked();
	virtual void scrollLayerMoved(cocos2d::CCPoint pos);

	// zyann addition
	// void updateColorForPage();

	cocos2d::ccColor3B colorForPage(int page);
	cocos2d::ccColor3B getColorValue(int pageA, int pageB, float t);

	BoomScrollLayerDelegate* m_bslDelegate; // 0x10c
	float m_winWidth;                       // 0x110  (stored from winSize.width in init)
	cocos2d::CCSprite* m_background;        // 0x114
	cocos2d::CCSprite* m_ground;            // 0x118
	BoomScrollLayer* m_scrollLayer;         // 0x11c
};
#endif