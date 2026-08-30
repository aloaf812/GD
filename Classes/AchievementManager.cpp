#include "AchievementManager.h"
#include "AchievementNotifier.h"

#include "RT_COCOS/CCContentManager.h"
USING_NS_CC;

AchievementManager::AchievementManager()
{
	m_allAchievements = nullptr;
    // unk_0xec = 0;
	m_reportedAchievements = nullptr;
	m_dontNotifyAch = false;
}

AchievementManager* AchievementManager::sharedState()
{
    static AchievementManager* pAchManager = NULL;
    if (!pAchManager)
    {
        pAchManager = new AchievementManager();
        pAchManager->init();
    }
    
    return pAchManager;
}

bool AchievementManager::init()
{
	m_reportedAchievements = CCDictionary::create();
	m_reportedAchievements->retain();
	m_allAchievements = CCContentManager::sharedManager()->addDict("AchievementsDesc.plist", true);
	m_allAchievements->retain();
	return true;
}

void AchievementManager::notifyAchievementWithID(char const* achID)
{
	if (!m_dontNotifyAch) {
		if (m_allAchievements->objectForKey(achID)) {
			CCDictionary* tempDict = (CCDictionary*)m_allAchievements->objectForKey(achID);
			const char* title = tempDict->valueForKey("title")->getCString();
			const char* description = tempDict->valueForKey("achievedDescription")->getCString();
			const char* icon = tempDict->valueForKey("icon")->getCString();
			AchievementNotifier::sharedState()->notifyAchievement(title, description, icon);
		}
	}
}

void AchievementManager::reportAchievementWithID(char const* achID, int percentage, bool param_3)
{
	if (!isAchievementEarned(achID)) {
		if (percentForAchievement(achID) < percentage) {
			/* imma do this later it's 10pm rn
			this_00 = (CCDictionary *)(this->data).offset_0x8;
      		pCVar3 = (CCObject *)cocos2d::CCString::createWithFormat("%i",percentage);
      		std::string(&pcStack_24,achID,&pAStack_28);
      		cocos2d::CCDictionary::setObject(this_00,pCVar3,(string *)&pcStack_24);
      		FUN_003b16dc(&pcStack_24);
      		pAVar2 = (AchievementManager *)reportPlatformAchievementWithID(this,achID,percentage);*/
		}
		if ((99 < percentage) && (!param_3)) {
			AchievementManager* pAchManager = sharedState();
			pAchManager->notifyAchievementWithID(achID);
		}
	}
}

bool AchievementManager::isAchievementEarned(char const* achID)
{
	return 99 < percentForAchievement(achID);
}

bool AchievementManager::areAchievementsEarned(CCArray* achSet)
{
	return true;
}

int AchievementManager::percentForAchievement(char const* achID)
{
	return m_reportedAchievements->valueForKey(achID)->intValue();;
}
