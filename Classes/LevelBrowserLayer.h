#ifndef __GeometryDash__LevelBrowserLayer__
#define __GeometryDash__LevelBrowserLayer__

#include "cocos2d.h"
#include "GJSearchObject.h"
#include "TextArea.h"

// class LevelBrowserLayer : public cocos2d::CCLayer, public LevelManagerDelegate {
class LevelBrowserLayer : public cocos2d::CCLayer {
public:
	static cocos2d::CCScene* scene(GJSearchObject* searchObject);
	static LevelBrowserLayer* create(GJSearchObject* searchObject);
	bool init(GJSearchObject* searchObject);

	void isCorrect(char const*);
	void loadLevelsFinished(cocos2d::CCArray*, char const*);

	void onNew(cocos2d::CCObject* sender);

	TextArea* m_noInternet; // 0x110
	GJSearchObject* m_searchObject; // 0x124
	cocos2d::CCLabelBMFont* m_countText; // 0x128
	// LoadingCircle* m_circle; // 0x138
};

#endif