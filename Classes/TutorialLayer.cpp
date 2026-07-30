#include "TutorialLayer.h"
USING_NS_CC;

bool TutorialLayer::init() {

	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
		return false;

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	unk_0x1a0 = CCLayer::create();
	this->addChild(unk_0x1a0);

	unk_0x1a4 = CCLayer::create();
	this->addChild(unk_0x1a4);

	// the rest

	return true;
}

