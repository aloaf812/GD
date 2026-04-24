#include "FLAlertLayer.h"
#include "TextArea.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
USING_NS_CC;

FLAlertLayer* FLAlertLayer::create(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width)
{
	FLAlertLayer* pRet = new FLAlertLayer();
	if (pRet && pRet->init(protocol, title, caption, button1, button2, width))
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

bool FLAlertLayer::init(FLAlertLayerProtocol* protocol, char const* title, char const* caption, char const* button1, char const* button2, float width) {
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
		return false;

	return true;
}

void FLAlertLayer::show() 
{
	// top ten ways to avoid decompiling a whole function:
	this->setVisible(true);
}