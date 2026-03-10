#include "FLAlertLayer.h"
#include "TextArea.h"
#include "RT_COCOS/CCMenuItemSpriteExtra.h"
#include "cocos-ext.h"
USING_NS_CC;

bool FLAlertLayer::init(FLAlertLayerProtocol* protocol, char const* title, std::string caption, char const* button1, char const* button2, float unk1) {
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
		return false;

	return true;
}