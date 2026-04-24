#ifndef __TUTORIAL_LAYER_H__
#define __TUTORIAL_LAYER_H__

#include "cocos2d.h"
#include "FLAlertLayer.h"

class TutorialLayer : public FLAlertLayer {
public:
	CREATE_FUNC(TutorialLayer);
	virtual bool init();
};

#endif /* defined(__TUTORIAL_LAYER_H__) */
