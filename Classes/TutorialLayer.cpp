#include "TutorialLayer.h"
USING_NS_CC;

TutorialLayer* TutorialLayer::create()
{
	TutorialLayer* pRet = new TutorialLayer();
	if (pRet && pRet->init())
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

