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
    // we won't do this here: m_mainLevels = CCContentManager::sharedManager()->addDict("LevelData.plist", true);
    // this is really just a desperate attempt to get this to work
    // while it does work, it isn't really the greatest option
    m_mainLevels = CCDictionary::createWithContentsOfFile("LevelData.plist");
    CCString* levelString = (CCString*)m_mainLevels->objectForKey("1");
    m_temp = levelString->getCString();
    return true;
}

std::string LocalLevelManager::getMainLevelString(int level)
{
    return m_temp;
}

void LocalLevelManager::setup()
{

}