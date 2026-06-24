#include "LocalLevelManager.h"
#include "RT_COCOS/CCContentManager.h"
USING_NS_CC;

LocalLevelManager::LocalLevelManager()
{
    m_mainLevels = nullptr;
}

LocalLevelManager* LocalLevelManager::sharedState()
{
    static LocalLevelManager* gLocalLevelManager = NULL;
    if (!gLocalLevelManager)
    {
        gLocalLevelManager = new LocalLevelManager();
        gLocalLevelManager->init();
    }
    
    return gLocalLevelManager;
}

bool LocalLevelManager::init()
{
	m_saveFile = "CCLocalLevels.dat";
	m_mainLevels = CCContentManager::sharedManager()->addDict("LevelData.plist", true);
	m_mainLevels->retain();
    return true;
}

std::string LocalLevelManager::getMainLevelString(int level)
{
	level = 1; // temporary fix because c++
	return m_mainLevels->valueForKey(CCString::createWithFormat("%i", level)->getCString())->getCString();
}

void LocalLevelManager::setup()
{
	unk_0xec = true;
	GManager::load();
}