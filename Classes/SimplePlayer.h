#ifndef _SIMPLE_PLAYER_H
#define _SIMPLE_PLAYER_H

#include "cocos2d.h"
#include <stdio.h>

enum class IconType {
    Cube = 0,
    Ship = 1,
    Ball = 2,
    UFO = 3,
    Special = 99
};

class SimplePlayer : public cocos2d::CCSprite {
public:
    SimplePlayer();
    static SimplePlayer* create(int iconID);
    bool init(int iconID);
};

#endif