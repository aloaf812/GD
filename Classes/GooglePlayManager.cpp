#include "GooglePlayManager.h"
USING_NS_CC;

GooglePlayManager* GooglePlayManager::sharedState()
{
	static GooglePlayManager* gGPM = NULL;
	if (!gGPM)
	{
		gGPM = new GooglePlayManager();
		gGPM->init();
	}

	return gGPM;
}

bool GooglePlayManager::init()
{
	return true;
}