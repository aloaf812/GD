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

	// unk_0x10c = unk;
	// unk_0x110 = unk;
	// unk_0x114 = unk;
	// unk_0x11c = unk;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	unk_0x118 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
	unk_0x118->setScale(0.85f);
	this->addChild(unk_0x118, 1);

	// yeah this function is pretty complicated soooooooo
	// TODO: whenever i care to properly finish it

    return true;
}

void GaragePage::onSelect(CCObject* sender)
{
	// whatever bro
}