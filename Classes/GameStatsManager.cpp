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
	m_liteAchievementsDict = CCDictionary::create();
	m_liteAchievementsDict->retain();
    return true;
}

int GameStatsManager::getStat(const char *stat)
{
    // this is just a temporary value while i actually decompile this class
    return 21739;
}

void GameStatsManager::incrementStat(char const* stat)
{
	incrementStat(stat, 1);
}

void GameStatsManager::incrementStat(char const* stat, int unk1)
{
	// todo
}

void GameStatsManager::dataLoaded(DS_Dictionary* dict)
{
	m_valueDict = dict->getDictForKey("GS_value");
	m_valueDict->retain();

	m_completedLevels = dict->getDictForKey("GS_completed");
	m_completedLevels->retain();
}


void GameStatsManager::encodeDataTo(DS_Dictionary* dict)
{
	dict->setDictForKey("GS_value", m_valueDict);
	dict->setDictForKey("GS_completed", m_completedLevels);
}

std::string GameStatsManager::getUniqueItemKey(char const* itemKey)
{
	return CCString::createWithFormat("unique_%s")->getCString();
}

bool GameStatsManager::hasUniqueItem(char const* itemKey)
{
	CCObject* item = m_valueDict->objectForKey(getUniqueItemKey(itemKey));
	return item != nullptr;
}