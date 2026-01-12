#ifndef __GeometryDash__PlayerObject__
#define __GeometryDash__PlayerObject__

#include "cocos2d.h"
#include "GameObject.h"

enum class GhostType {
	Disabled = 0,
	Enabled = 1,
};

class PlayerObject : public GameObject {
public:
    static PlayerObject* create(int player, int ship, cocos2d::CCLayer* layer);
    //virtual void update(float dt);
    bool init(int player, int ship, cocos2d::CCLayer* layer);
protected:
	cocos2d::CCLayer* m_layer;

	// all of the sprites
	cocos2d::CCSprite* m_iconSprite;
	cocos2d::CCSprite* m_iconSpriteSecondary;

	cocos2d::CCSprite* m_vehicleSprite;
	cocos2d::CCSprite* m_vehicleSpriteSecondary;

	cocos2d::CCSprite* m_iconGlow;
	cocos2d::CCSprite* m_vehicleGlow;

	GhostType m_ghostType;
};

#endif /* defined(__GeometryDash__PlayerObject__) */
