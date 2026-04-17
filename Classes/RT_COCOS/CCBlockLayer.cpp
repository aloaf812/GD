#include "CCBlockLayer.h"
USING_NS_CC;

bool CCBlockLayer::init() { 
	CCDirector* pDirector = CCDirector::sharedDirector();
	// pDirector->getTouchDispatcher()->setForcePrio(true);
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)))
		return false;
	
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	
	m_removeOnExit = true;

	return true;
}

void CCBlockLayer::customSetup() {}