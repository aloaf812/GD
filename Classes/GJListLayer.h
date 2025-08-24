#ifndef _GJ_LIST_LAYER_H_
#define _GJ_LIST_LAYER_H_

#include "cocos2d.h"

// temporary while i figure out exactly what goes on here
class BoomListView;

class GJListLayer : public cocos2d::CCLayerColor
{
public:
    static GJListLayer* create(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4);
};

#endif
