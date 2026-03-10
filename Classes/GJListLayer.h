#ifndef _GJ_LIST_LAYER_H_
#define _GJ_LIST_LAYER_H_

#include "cocos2d.h"
#include "BoomListView.h"

class GJListLayer : public cocos2d::CCLayerColor {
public:
    GJListLayer();
	static GJListLayer* create(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height);
	bool init(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height);
};

#endif