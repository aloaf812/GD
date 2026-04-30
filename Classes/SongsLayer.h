#ifndef __SONGS_LAYER_H__
#define __SONGS_LAYER_H__

#include "cocos2d.h"
#include "GJDropDownLayer.h"

class SongsLayer : public GJDropDownLayer {
public:
	static SongsLayer* create();
	void customSetup();
};

#endif /* __SONGS_LAYER_H__ */