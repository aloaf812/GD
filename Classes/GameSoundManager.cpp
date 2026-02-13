#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

GameSoundManager* GameSoundManager::sharedManager()
{
	static GameSoundManager* GSM = NULL;
	if (!GSM)
	{
		GSM = new GameSoundManager();
		GSM->init();
	}

	return GSM;
}

bool GameSoundManager::init() {
    return true;
}

void GameSoundManager::setup() {
	/*if (!BOOL_004c6998) {
		BOOL_004c6998 = true;
		asynchronousSetup(this);
		return;
	} ghidra what??? */ 
    return;
}

void GameSoundManager::playEffect(char const* filename, float pitch, float pan, float gain) {
	SimpleAudioEngine::sharedEngine()->playEffect(filename, true);
	// according to the humble antimatter before 1.7 these unknown params were set to 1.0, 0.0, and 1.0 respectively
	return;
}

void GameSoundManager::setBGMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	this->m_bgVol = volume;
}