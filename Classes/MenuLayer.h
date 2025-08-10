#ifndef __GeometryDash__MenuLayer__
#define __GeometryDash__MenuLayer__

#include "cocos2d.h"

class MenuLayer: public cocos2d::CCLayer {
public:
    static cocos2d::CCScene* scene();
    /**
    @brief Runs when the "More Games" button is pressed in the main menu 
    */
    void onMoreGames(cocos2d::CCObject* sender);
    // virtual bool init();
};

#endif