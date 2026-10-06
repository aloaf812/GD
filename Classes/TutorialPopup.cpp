#include "TutorialPopup.h"
USING_NS_CC;

bool TutorialPopup::init(std::string fileStr)
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
		return false;

	// todo
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	unk_0x1a0 = CCLayer::create();
	this->addChild(unk_0x1a0);

	return true;
}
