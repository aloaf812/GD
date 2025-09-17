#ifndef _PLAY_LAYER_H
#define _PLAY_LAYER_H

#include "cocos2d.h"
#include "GJBaseGameLayer.h"
#include "GJGameLevel.h"

class PlayLayer : public GJBaseGameLayer {
public:
    PlayLayer();
    static cocos2d::CCScene* scene(GJGameLevel* level);
    static PlayLayer* create(GJGameLevel* level);
    bool init(GJGameLevel* level);
    void onQuit();
};

#endif
