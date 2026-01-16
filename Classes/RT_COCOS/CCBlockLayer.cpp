#include "CCBlockLayer.h"
USING_NS_CC;

bool CCBlockLayer::init() { 
	CCDirector* pDirector = CCDirector::sharedDirector();
	// pDirector->getTouchDispatcher()->setForcePrio(true);
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125))) {
		this->setTouchEnabled(true);
		this->setKeypadEnabled(true);
		return false;
	}
	CCLOG("init CCBlockLayer");
	return true;
}

void CCBlockLayer::customSetup() {}