#include "GameStatsManager.h"
USING_NS_CC;


GameStatsManager* GameStatsManager::sharedState()
{
    static GameStatsManager* gGameStatsManager = NULL;
    if (!gGameStatsManager)
    {
        gGameStatsManager = new GameStatsManager();
        gGameStatsManager->init();
    }
    
    return gGameStatsManager;
}

bool GameStatsManager::init()
{
    m_unkDict1 = CCDictionary::create();
    m_unkDict1->retain();
    return true;
}

int GameStatsManager::getStat(const char *stat)
{
    // this is just a temporary value while i actually decompile this class
    return 21739;
}