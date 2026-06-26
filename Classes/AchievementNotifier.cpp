// decompiled by ItzZyann
// from GD 1.71 binary

#include "AchievementNotifier.h"
#include "AchievementBar.h"
#include "GameSoundManager.h"

USING_NS_CC;
static int s_achievementCount = 0; // zyann addition xd

AchievementNotifier::AchievementNotifier()
	: m_achArray(nullptr)
	, m_currentAch(nullptr)
{
}

AchievementNotifier::~AchievementNotifier()
{
	CC_SAFE_RELEASE(m_achArray);
	CC_SAFE_RELEASE(m_currentAch);
}

AchievementNotifier* AchievementNotifier::sharedState()
{
	static AchievementNotifier* s_pNotifier = nullptr;
	if (!s_pNotifier)
	{
		s_pNotifier = new AchievementNotifier();
		if (s_pNotifier && s_pNotifier->init())
		{
			s_pNotifier->retain();
		}
	}
	return s_pNotifier;
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
	if (bar)
	{
		m_achArray->addObject(bar);
		if (!m_currentAch)
		{
			showNextAchievement();
		}
	}
}

void AchievementNotifier::showNextAchievement()
{
	if (m_achArray->count() > 0)
	{
		float pitch = (s_achievementCount * 0.05f) + 1.0f;
		GameSoundManager::sharedManager()->playEffect("achievement_01.ogg", pitch, 0.0f, 0.3f);
		s_achievementCount++;

		m_currentAch = static_cast<AchievementBar*>(m_achArray->objectAtIndex(0));
		m_currentAch->retain();

		m_achArray->removeObjectAtIndex(0, false); // false to avoid immediate delete

		CCScene* runningScene = CCDirector::sharedDirector()->getRunningScene();
		if (runningScene)
		{
			runningScene->addChild(m_currentAch, 100);
		}

		m_currentAch->show();
	}
	else
	{
		s_achievementCount = 0;
	}
}

void AchievementNotifier::achievementDisplayFinished()
{
	if (m_currentAch)
	{
		m_currentAch->removeFromParent();
		CC_SAFE_RELEASE(m_currentAch);
		m_currentAch = nullptr;

		showNextAchievement();
	}
}

void AchievementNotifier::willSwitchToScene(cocos2d::CCScene* scene)
{
	// re-parent the currently visible bar into the new scene
	if (m_currentAch)
	{
		m_currentAch->retain();
		m_currentAch->removeFromParent();
		scene->addChild(m_currentAch, 100);
		m_currentAch->release();
	}

	// also re-create any queued bars so their parent references stay valid.
	// they have no parent yet (they haven't been shown), so nothing to reparent
	// but we make sure the array survives by simply keeping it. No action needed.
}