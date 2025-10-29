#include "AchievementBar.h"
USING_NS_CC;

AchievementBar::AchievementBar()
{

}

AchievementBar* AchievementBar::create(char const* title, char const* description, char const* icon)
{
    AchievementBar* pRet = new AchievementBar();
    if (pRet && pRet->init(title, description, icon))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool AchievementBar::init(char const* title, char const* description, char const* icon)
{
	CCLOG("creating achievement bar for %s", title);
	return true;
}