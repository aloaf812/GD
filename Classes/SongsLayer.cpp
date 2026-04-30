#include "SongsLayer.h"
USING_NS_CC;

SongsLayer* SongsLayer::create()
{
	SongsLayer *pRet = new SongsLayer();
	if (pRet && pRet->init("Soundtracks"))
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

void SongsLayer::customSetup()
{

}