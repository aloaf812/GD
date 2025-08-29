#ifndef _MENU_GAME_LAYER_H
#define _MENU_GAME_LAYER_H

#include "cocos2d.h"

class MenuGameLayer: public cocos2d::CCLayer {
public:
    static MenuGameLayer* create();
    virtual bool init();
    cocos2d::ccColor3B getBGColor(int p0);
};

#endif /* defined(_MENU_GAME_LAYER_H) */
