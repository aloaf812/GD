#ifndef _MENU_GAME_LAYER_H
#define _MENU_GAME_LAYER_H

#include "PlayerObject.h"
#include "cocos2d.h"
/**
@brief The background layer of the main menu with the scrolling BG/ground and the jumping icons
*/
class MenuGameLayer : public cocos2d::CCLayer {
public:
	MenuGameLayer();
	CREATE_FUNC(MenuGameLayer);
    bool init();
    void update(float delta);
	void tryJump();

protected:
	PlayerObject* m_playerObject; // 0x114
    cocos2d::CCSprite* m_backgroundSprite; // 0x118
    cocos2d::CCSprite* m_groundSprite; // 0x11c
    cocos2d::CCLayer* m_groundLayer; // 0x120
	float m_groundSpeed; // 0x124
    float m_backgroundSpeed; // 0x128
};

#endif /* defined(_MENU_GAME_LAYER_H) */