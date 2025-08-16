#ifndef __GAME_SOUND_MANAGER_H__
#define __GAME_SOUND_MANAGER_H__

#include "cocos2d.h"
/**
@brief  Manages the game's music and sound effects
*/
class GameSoundManager : public cocos2d::CCNode {
public:
    bool init();
    void setup();
    static GameSoundManager* sharedState() {
        return 0;
    }
};

#endif