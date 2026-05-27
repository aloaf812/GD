#ifndef __GeometryDash__ExtendedLayer__
#define __GeometryDash__ExtendedLayer__

#include "cocos2d.h"
#include "BoomScrollLayer.h"

class BoomScrollLayerDelegate;

class ExtendedLayer : public cocos2d::CCLayer {
public:
	static ExtendedLayer* create();
    bool init();

	CC_SYNTHESIZE(BoomScrollLayerDelegate*, m_delegate, Delegate);
};

#endif /* defined(__GeometryDash__ExtendedLayer__) */
