#ifndef __STATS_LAYER_H__
#define __STATS_LAYER_H__

#include "cocos2d.h"
#include "GJDropDownLayer.h"

class StatsLayer : public GJDropDownLayer {
public:
	static StatsLayer* create();
	void customSetup();
};

#endif /* __STATS_LAYER_H__ */