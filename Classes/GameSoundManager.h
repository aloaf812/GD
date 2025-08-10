#ifndef __GeometryDash__GameSoundManager__
#define __GeometryDash__GameSoundManager__

#include "cocos2d.h"
/**
@brief  Manages the game's music and sound effects
*/
class GameSoundManager : public cocos2d::CCNode {
    bool init();
    void setup();
    static GameSoundManager* GameSoundManager();
};

#endif