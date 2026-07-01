#include "MoreGamesManager.h"
USING_NS_CC;

MoreGamesManager* MoreGamesManager::sharedState()
{
	static MoreGamesManager* gMGM = NULL;
	if (!gMGM)
	{
		gMGM = new MoreGamesManager();
		gMGM->init();
	}

	return gMGM;
}

bool MoreGamesManager::init()
{
	firstLoad();
	return true;
}

void MoreGamesManager::firstLoad()
{
	m_moreGamesString = "mu_boom_mm";
	m_lastDay = -1;
	m_lastMonth = -1;
	m_hasNewGames = false;
}