#ifndef __GeometryDash__LevelBrowserLayer__
#define __GeometryDash__LevelBrowserLayer__

#include "cocos2d.h"
#include "GJSearchObject.h"

// class LevelBrowserLayer : public cocos2d::CCLayer, public LevelManagerDelegate {
class LevelBrowserLayer : public cocos2d::CCLayer {
public:
	static cocos2d::CCScene* scene(GJSearchObject* searchObject);
	static LevelBrowserLayer* create(GJSearchObject* searchObject);
	bool init(GJSearchObject* searchObject);
};

#endif