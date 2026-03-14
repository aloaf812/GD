#ifndef _MENU_GAME_LAYER_H
#define _MENU_GAME_LAYER_H

#include "PlayerObject.h"
#include "cocos2d.h"

class MenuGameLayer : public cocos2d::CCLayer {
public:
	MenuGameLayer();
	CREATE_FUNC(MenuGameLayer);
    bool init();
    void update(float delta);

protected:
	// these undocumented variables aren't actually in the game's code
	// the math that these variables are used in is also wrong and both issues will be fixed soon
	float m_bgOffset;
	float m_groundOffset;
	float m_bgWidth;
	float m_groundWidth;
	PlayerObject* m_playerObject; // 0x114
    cocos2d::CCSprite* m_backgroundSprite; // 0x118
    cocos2d::CCSprite* m_groundSprite; // 0x11c
    cocos2d::CCLayer* m_groundLayer; // 0x120
	float m_groundSpeed; // 0x124
    float m_backgroundSpeed; // 0x128
};

#endif /* defined(_MENU_GAME_LAYER_H) */