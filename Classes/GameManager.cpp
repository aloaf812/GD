#include "GameManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


bool GameManager::init(){
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
    GameManager::loadBackground(bgID);
    CCString *this_00 = CCString::createWithFormat("game_bg_%02d_001.png", bgID);
    return this_00->CCString::getCString();
}

void GameManager::fadeInMusic(char const *fileName){
    return;
}

GameManager* GameManager::sharedState()
{
    return NULL;
}

void GameManager::reportAchievementWithID(char const* ach_ID, int percentage, bool param_3){
    return;
}