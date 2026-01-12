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
    static GameSoundManager* sharedManager() {
        return 0;
    }
	void playEffect(char const* filename, float param_2, float param_3, float param_4);
};

#endif