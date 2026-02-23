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
	static GameSoundManager* sharedManager();
	void playEffect(char const* filename, float pitch, float pan, float gain);
	void setBGMusicVolume(float volume);
	void asynchronousSetup();
	void preload();
	
	CC_SYNTHESIZE(float, m_bgVol, BGVol); // 0x3f
	CC_SYNTHESIZE_READONLY(int, m_state, State); // 0x3e
};

#endif