#include "AchievementNotifier.h"
#include "AchievementBar.h"

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
    return true;
}

void AchievementNotifier::notifyAchievement(char const* title, char const* description, char const* icon)
{

}

void AchievementNotifier::showNextAchievement()
{

}

void AchievementNotifier::achievementDisplayFinished()
{

}

void AchievementNotifier::willSwitchToScene(cocos2d::CCScene* scene)
{

}