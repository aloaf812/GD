#include "AchievementsLayer.h"
USING_NS_CC;

AchievementsLayer* AchievementsLayer::create()
{
	AchievementsLayer* pRet = new AchievementsLayer();
	if (pRet && pRet->init("Achievements"))
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