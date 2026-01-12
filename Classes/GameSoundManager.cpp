#include "GameSoundManager.h"
USING_NS_CC;

bool GameSoundManager::init() {
    return true;
}

void GameSoundManager::setup() {
    return;
}

void GameSoundManager::playEffect(char const* filename, float param_2, float param_3, float param_4) {
	// according to the humble antimatter before 1.7 these unknown params were set to 1.0, 0.0, and 1.0 respectively
	return;
}