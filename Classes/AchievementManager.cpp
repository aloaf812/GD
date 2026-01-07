#include "AchievementManager.h"
#include "AchievementNotifier.h"

#include "RT_COCOS/CCContentManager.h"
USING_NS_CC;

AchievementManager::AchievementManager()
{
	this->m_achDict = nullptr;                                                    
    // (this_00->data).offset_0x4 = 0;
    // (this_00->data).offset_0x8 = (CCObject *)0x0;
	this->m_dontNotifyAch = false;
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
	m_reportedAchDict = CCDictionary::create();
    m_reportedAchDict->retain();
    // todo: add CCContentManager
    CCContentManager* pContentManager = CCContentManager::sharedManager();
    m_achDict = pContentManager->addDict("AchievementsDesc.plist", true);
    m_achDict->retain();
	return true;
}

void AchievementManager::notifyAchievementWithID(char const* achID)
{
    // houston, we have a problem.
    CCLOG("notifying achievement %s", achID);
	if (this->m_dontNotifyAch == false) {
		/*if (m_achDict->objectForKey(achID) != nullptr) {
			const char* title = m_achDict->valueForKey("title")->getCString();
            CCLOG(title);
			const char* description = m_achDict->valueForKey("achievedDescription")->getCString();
            CCLOG(description);
			const char* icon = m_achDict->valueForKey("icon")->getCString();
            CCLOG(icon);
            AchievementNotifier* pAchNotifier = AchievementNotifier::sharedState();
			pAchNotifier->notifyAchievement(title, description, icon);
		}*/
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
	return false;
}

bool AchievementManager::areAchievementsEarned(CCArray* achSet)
{
	return true;
}

int AchievementManager::percentForAchievement(char const* achID)
{
	return 20;
}
