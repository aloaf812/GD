#ifndef _MENU_GAME_LAYER_H
#define _MENU_GAME_LAYER_H

#include "GJGroundLayer.h"
#include "PlayerObject.h"
#include "cocos2d.h"

class MenuGameLayer : public cocos2d::CCLayer {
    float m_deltaCount;
    int m_initCount;
    cocos2d::CCPoint m_unused1;
    PlayerObject* m_playerObject;
    cocos2d::CCSprite* m_backgroundSprite;
    cocos2d::CCMenu* bgSprites;
    // GJGroundLayer* m_groundLayer;
    float m_backgroundSpeed;
public:
    MenuGameLayer();
    static MenuGameLayer* create();
    bool init();
    void update(float delta);
};

#endif /* defined(_MENU_GAME_LAYER_H) */