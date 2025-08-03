#ifndef __GeometryDash__GameManager__
#define __GeometryDash__GameManager__

#include "cocos2d.h"
#include "GManager.h"
#include <stdio.h>

class GameManager: public GManager {
public:
    static GameManager* sharedState();
    char const* getBGTexture(int id);
    // void fadeInMusic(char const*);
    virtual bool init();
    // void loadBackground(int p0);
};

#endif /* defined(__GeometryDash__GameManager__) */
