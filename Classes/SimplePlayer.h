#ifndef _SIMPLE_PLAYER_H_
#define _SIMPLE_PLAYER_H_

#include "cocos2d.h"

class SimplePlayer : public cocos2d::CCSprite {

};

enum class IconType {
        Cube = 0,
        Ship = 1,
        Ball = 2,
        UFO = 3,
        Special = 99
}

#endif