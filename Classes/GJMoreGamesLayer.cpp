#include "GJMoreGamesLayer.h"
USING_NS_CC;

GJMoreGamesLayer* GJMoreGamesLayer::create()
{
	GJMoreGamesLayer *pRet = new GJMoreGamesLayer();
	if (pRet && pRet->init("RobTop Games"))
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