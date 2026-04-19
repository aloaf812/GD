#include "AchievementNotifier.h"
#include "GameSoundManager.h"
USING_NS_CC;

AchievementNotifier::AchievementNotifier()
{

}

AchievementNotifier* AchievementNotifier::sharedState()
{
    static AchievementNotifier* pAchNotifier = NULL;
    if (!pAchNotifier)
    {
        pAchNotifier = new AchievementNotifier();
        pAchNotifier->init();
    }
    
    return pAchNotifier;
}

bool AchievementNotifier::init()
{
	m_achArray = CCArray::create();
	m_achArray->retain();
    return true;
}

void AchievementNotifier::notifyAchievement(char const* title, char const* description, char const* icon)
{
	AchievementBar* bar = AchievementBar::create(title, description, icon);
	m_achArray->addObject(bar);
	//if (m_currentAch == NULL) {
	showNextAchievement(); 
		//return;
	//}
	return;
}

void AchievementNotifier::showNextAchievement()
{
	if (!m_achArray->count()) {
		return;
	}
	GameSoundManager::sharedManager()->playEffect("achievement_01.ogg", 1.0f, 0.0f, 1.0f);
	// what??: DAT_004c6600 = (GameSoundManager *)((int)DAT_004c6600 + 1);
	m_currentAch = (AchievementBar*)m_achArray->objectAtIndex(0);
	m_currentAch->show();
	return;
}

void AchievementNotifier::achievementDisplayFinished()
{
	CCNode::removeMeAndCleanup();

	if (m_currentAch != nullptr) {
		m_currentAch->release();
	}

	m_currentAch = nullptr;
	this->showNextAchievement();
}

void AchievementNotifier::willSwitchToScene(cocos2d::CCScene* scene)
{

}