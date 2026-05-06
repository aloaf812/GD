#include "GJListLayer.h"
USING_NS_CC;

GJListLayer* GJListLayer::create(BoomListView* listView, const char* title, ccColor4B color, float width, float height)
{
    GJListLayer* pRet = new GJListLayer();
    
	if (pRet->init(listView, title, color, width, height)) {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

GJListLayer::GJListLayer()
{
    
}

bool GJListLayer::init(BoomListView* listView, char const* title, ccColor4B color, float width, float height)
{
    if (!CCLayerColor::initWithColor(color, width, height))
        return false;
    
    CCSprite* tableBottom = CCSprite::createWithSpriteFrameName("GJ_table_bottom_001.png");
	tableBottom->setPosition(ccp(width * 0.5, -10.0));
	this->addChild(tableBottom, 10);

	char const* tbSprite;
	if (title)
		tbSprite = "GJ_table_top_001.png";
	else
		tbSprite = "GJ_table_top02_001.png";

	CCSprite* tableTop = CCSprite::createWithSpriteFrameName(tbSprite);
	tableTop->setPosition(ccp(width * 0.5f, (height - 5.0f) + 20.0f));
	tableTop->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(tableTop, 10);


	CCSprite* tableLeft = CCSprite::createWithSpriteFrameName("GJ_table_side_001.png");
	tableLeft->setAnchorPoint(ccp(0.0f, 0.0f));
	this->addChild(tableLeft, 9);
	tableLeft->setPosition(ccp(-20.0f, 0.0f));
	tableLeft->setScaleY(height / tableLeft->getContentSize().height); // wow robtop i praise this code's stupidity

	CCSprite* tableRight = CCSprite::createWithSpriteFrameName("GJ_table_side_001.png");
	tableRight->setAnchorPoint(ccp(1.0f, 0.0f));
	this->addChild(tableRight, 9);
	tableRight->setPosition(ccp(width + 20.0f, 0.0f));
	tableRight->setScaleY(tableLeft->getScaleY());
	tableRight->setFlipX(true);
	
	if (title) {
		CCLabelBMFont* titleFnt = CCLabelBMFont::create(title, "bigFont.fnt");
		this->addChild(titleFnt, 11);
		titleFnt->setScale(0.8f);
		titleFnt->setPosition(ccp(0.0f, 3.0f) + tableTop->getPosition());
	}

	if (listView) {
		this->addChild(listView, 6);
		listView->setTag(9);
	}

    return true;
}