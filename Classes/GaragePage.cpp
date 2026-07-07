#include "GaragePage.h"
USING_NS_CC;


GaragePage* GaragePage::create(IconType type, GJGarageLayer* garage)
{
	GaragePage* ret = new GaragePage();
	if (ret) {
		if (ret->init(type, garage)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
	}

	return NULL;
}

bool GaragePage::init(IconType type, GJGarageLayer* garage)
{

	if (!CCLayer::init())
		return false;
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	unk_0x118 = CCSprite::create("GJ_select_001.png");

	// yeah this function is pretty complicated soooooooo
	// TODO: whenever i care to properly finish it

    return true;
}

void GaragePage::onSelect(CCObject* sender)
{
	// whatever bro
}