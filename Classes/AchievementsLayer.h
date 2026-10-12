#ifndef _ACHIEVEMENTS_LAYER_H_
#define _ACHIEVEMENTS_LAYER_H_

#include "cocos2d.h"
#include "GJDropDownLayer.h"

class AchievementsLayer : public GJDropDownLayer {
public:
	static AchievementsLayer* create();
	void customSetup();
};

#endif /* __ACHIEVEMENTS_LAYER_H__ */