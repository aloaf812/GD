#ifndef __GeometryDash__ExtendedLayer__
#define __GeometryDash__ExtendedLayer__

#include "cocos2d.h"
#include "BoomScrollLayer.h"

class BoomScrollLayerDelegate;

class ExtendedLayer : public cocos2d::CCLayer {
public:
	static ExtendedLayer* create();
    bool init();

	void setPosition(cocos2d::CCPoint const &position);

	CC_SYNTHESIZE(BoomScrollLayerDelegate*, m_delegate, Delegate); // 0x10c
};

#endif /* defined(__GeometryDash__ExtendedLayer__) */
