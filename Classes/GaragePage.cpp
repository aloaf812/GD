#include "GaragePage.h"
USING_NS_CC;


GaragePage* GaragePage::create(IconType type, GJGarageLayer* garage, SEL_MenuHandler selector)
{
	GaragePage* ret = new GaragePage();
	if (ret) {
		if (ret->init(type, garage, selector)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
	}

	return NULL;
}

bool GaragePage::init(IconType type, GJGarageLayer* garage, SEL_MenuHandler selector)
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