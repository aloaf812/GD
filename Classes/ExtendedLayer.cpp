#include "ExtendedLayer.h"
USING_NS_CC;

bool ExtendedLayer::init()
{   
    return CCLayer::init();
}

ExtendedLayer* ExtendedLayer::create() {
	ExtendedLayer* ret = new ExtendedLayer();
	if (ret) {
		if (ret->init()) {
			ret->autorelease();
			return ret;
		}

		delete ret;
	}

	return NULL;
}