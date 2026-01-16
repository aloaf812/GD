#ifndef _CC_BLOCK_LAYER_H
#define _CC_BLOCK_LAYER_H

#include "cocos2d.h"

class CCBlockLayer : public cocos2d::CCLayerColor {
public:
	virtual bool init();
	virtual void customSetup();
};
#endif