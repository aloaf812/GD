#ifndef __GeometryDash__PlayerObject__
#define __GeometryDash__PlayerObject__

#include "cocos2d.h"
#include "GameObject.h"

class PlayerObject : public GameObject {
public:
    static PlayerObject* create(int player, int ship, cocos2d::CCLayer* layer);
    //virtual void update(float dt);
    bool init(int player, int ship, cocos2d::CCLayer* layer);
};

#endif /* defined(__GeometryDash__PlayerObject__) */
