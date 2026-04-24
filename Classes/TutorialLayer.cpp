#include "TutorialLayer.h"
USING_NS_CC;

bool TutorialLayer::init() {

	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
		return false;

	return true;
}