#include "GameManager.h"

#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>

USING_NS_CC;
using namespace CocosDenshion;


bool GameManager::init(){
    // just list variables here as their initial state until a proper save system has been implemented
    m_clickedEditor = false;
    m_clickedGarage = false;
    // weird function here
    // creates "CCGameManager.dat" file
    return true;
}

void GameManager::loadBackground(int param_1)
{
    int bgID = param_1;
    if (3 < param_1) {
        bgID = 4;
    }
    if (param_1 < 1) {
        bgID = 1;
    }
    return;
}

char const* GameManager::getBGTexture(int id)
{
    int bgID = id;
    if (3 < id) {
        bgID = 4;
    }
    if (id < 1) {
        bgID = 1;
    }
	this->loadBackground(bgID);
	return cocos2d::CCString::createWithFormat("game_bg_%02d_001.png", bgID)->getCString();
}

/* char const* GameManager::iconKey(int id, IconType type){
    switch (type) {
        case IconType::Cube:
        default:
            return cocos2d::CCString::createWithFormat("i_%i", id)->getCString();
        case IconType::Ship:
            return cocos2d::CCString::createWithFormat("ship_%i", id)->getCString();
        case IconType::Ball:
            return cocos2d::CCString::createWithFormat("ball_%i", id)->getCString();
        case IconType::Ufo:
            return cocos2d::CCString::createWithFormat("bird_%i", id)->getCString();
        case IconType::Special:
            return cocos2d::CCString::createWithFormat("special_%i", id)->getCString();
        }
    }
}
*/

void GameManager::fadeInMusic(char const *fileName){
    // GameSoundManager* GSM = GameSoundManager::sharedState();
    if (true)
    {
        // todo: implement actual fading
        SimpleAudioEngine* SAE = SimpleAudioEngine::sharedEngine();
        SAE->setBackgroundMusicVolume(100.0f);
        SAE->playBackgroundMusic(fileName, true);
    }
    return;
}

void GameManager::syncPlatformAchievements()
{
    
}

GameManager* GameManager::sharedState()
{
    static GameManager* gGameManager = NULL;
    if (!gGameManager)
    {
        gGameManager = new GameManager();
        gGameManager->init();
    }
    
    return gGameManager;
}

void GameManager::reportAchievementWithID(char const* ach_ID, int percentage, bool param_3)
{
    // todo: implement achievements
}

void GameManager::followTwitter()
{
    
}

void GameManager::likeFacebook()
{
    
}