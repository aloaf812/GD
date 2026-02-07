#ifndef _MENU_GAME_LAYER_H
#define _MENU_GAME_LAYER_H

#include "PlayerObject.h"
#include "cocos2d.h"

class MenuGameLayer : public cocos2d::CCLayer {
    float m_bgOffset;
    float m_groundOffset;
    float m_bgWidth;
    float m_groundWidth;
    cocos2d::CCSprite* m_groundSprite;
    cocos2d::CCLayer* m_groundLayer;
    PlayerObject* m_playerObject; // 0x114
    cocos2d::CCSprite* m_backgroundSprite; // 0x118
    float m_backgroundSpeed;
public:
	MenuGameLayer();
	CREATE_FUNC(MenuGameLayer);
    bool init();
    void update(float delta);
};

#endif /* defined(_MENU_GAME_LAYER_H) */