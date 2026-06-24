#include "AchievementManager.h"
#include "AchievementNotifier.h"

// #include "RT_COCOS/CCContentManager.h"
// re-enable when CCContentManager is ready

USING_NS_CC;

AchievementManager::AchievementManager()
	: m_allAchievements(nullptr)
	, m_reportedAchievements(nullptr)
	, m_dontNotifyAch(false)
{
}

AchievementManager::~AchievementManager()
{
	CC_SAFE_RELEASE(m_allAchievements);
	CC_SAFE_RELEASE(m_reportedAchievements);
}

AchievementManager* AchievementManager::sharedState()
{
	static AchievementManager* pAchManager = nullptr;
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

	// TODO: swap to CCContentManager when ready
	// CCContentManager* pContentManager = CCContentManager::sharedManager();
	// m_allAchievements = pContentManager->addDict("AchievementsDesc.plist", true);

	m_allAchievements = CCDictionary::createWithContentsOfFile("AchievementsDesc.plist");
	m_allAchievements->retain();
	return true;
}

void AchievementManager::notifyAchievementWithID(char const* achID)
{
	if (m_dontNotifyAch)
	{
		return;
	}

	CCDictionary* tempDict = dynamic_cast<CCDictionary*>(m_allAchievements->objectForKey(achID));
	if (!tempDict)
	{
		return;
	}

	const char* title = tempDict->valueForKey("title")->getCString();
	const char* description = tempDict->valueForKey("achievedDescription")->getCString();
	const char* icon = tempDict->valueForKey("icon")->getCString();

	CCLog("[AchLog] Notifying: %s | %s | %s", title, description, icon);

	AchievementNotifier::sharedState()->notifyAchievement(title, description, icon);
}

void AchievementManager::reportAchievementWithID(char const* achID, int percentage, bool skipNotify)
{
	if (isAchievementEarned(achID))
		return;

	if (percentForAchievement(achID) < percentage)
	{
		// TODO: persist the new percentage
		// CCString* pct = CCString::createWithFormat("%i", percentage);
		// m_reportedAchievements->setObject(pct, achID);
		// reportPlatformAchievementWithID(achID, percentage);
	}

	// Notify the player only when fully completed (100%) and not suppressed
	if (percentage > 99 && !skipNotify)
	{
		notifyAchievementWithID(achID);
	}
}

bool AchievementManager::isAchievementEarned(char const* achID)
{
	// TODO: check m_reportedAchievements / platform layer for 100%
	return false;
}

bool AchievementManager::areAchievementsEarned(CCArray* achSet)
{
	// TODO: iterate achSet and call isAchievementEarned for each entry
	return true;
}

int AchievementManager::percentForAchievement(char const* achID)
{
	// TODO: look up persisted percentage from m_reportedAchievements
	// Returning 0 so the < percentage guard in reportAchievementWithID actually passes.
	return 0;
}