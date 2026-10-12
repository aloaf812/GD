#include "StatsLayer.h"
USING_NS_CC;

StatsLayer* StatsLayer::create()
{
	StatsLayer* pRet = new StatsLayer();
	if (pRet && pRet->init("Stats"))
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